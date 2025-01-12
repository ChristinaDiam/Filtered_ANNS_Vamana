#include "graph.h"
#include <immintrin.h>
#include <omp.h>

// Function to calculate Euclidean Distance
double EuclideanDistance(const vector<float>& node1, const vector<float>& node2){

    if (node1.size() != node2.size()) {
        throw invalid_argument("Vectors have different size.");
    }

    int size = node1.size();

    // Euclidean distance using SIMD (AVX/AVX2)
    
    // Initialize a vector register for the sum
    __m256 sum_v8 = _mm256_setzero_ps(); 

    // Process 8 elements at a time
    for (int i = 0; i <= size - 8; i += 8) {
        // Load input vectors into registers
        __m256 node1_v8 = _mm256_loadu_ps(&node1[i]);
        __m256 node2_v8 = _mm256_loadu_ps(&node2[i]);

        // Compute (node1[i] - node2[i])^2 + sum_v8 using FMA
        __m256 diff_v8 = _mm256_sub_ps(node1_v8, node2_v8);
        sum_v8 = _mm256_fmadd_ps(diff_v8, diff_v8, sum_v8);
    }

    // Reduce the vector register to a scalar sum
    float temp[8];
    _mm256_storeu_ps(temp, sum_v8);
    float sum = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7];

    // Handle any remaining elements
    for (int i = (size / 8) * 8; i < size; ++i) {
        float diff = node1[i] - node2[i];
        sum += diff * diff;
    }

    float Euclidean = sqrt(sum);
    return Euclidean;
} 


vector<int> choose_N_random_nodes(int N, int start, int finish, int self){

    int i;
    vector<int> choosableNodes;

    for(i = start; i <= finish; i++)
    {
        if(i == self)
            continue;

        choosableNodes.push_back(i);
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(choosableNodes.begin(), choosableNodes.end(), gen);

    return vector<int>(choosableNodes.begin(), choosableNodes.begin() + N);
}


// Creates a random R-regular directed graph
vector<vector<edge>> CreateGraph(const vector<vector<float>>& data, int size, int R){

    // Create adjacency list
    vector<vector<edge>> Graph(size);

    if (size >= 30000){

        // Multithreading for big datasets
        #pragma omp parallel for
        for (int i = 0; i < size; ++i){
            vector<int> randomNeighbors = choose_N_random_nodes(R, 0, size - 1, i);
            vector<edge> local_edges;

            for (int j = 0; j < R; ++j){
                float distance = EuclideanDistance(data[i], data[randomNeighbors[j]]);
                local_edges.emplace_back(randomNeighbors[j], distance);
            }

            Graph[i] = move(local_edges);
        }

    }else{ 

        // For every node of the graph connect R random neighbors
        for (int i = 0; i < size; ++i){

            vector<int> randomNeighbors = choose_N_random_nodes(R, 0, size-1, i);

            for (int j = 0; j < R; ++j){

                float distance = 0.0;   // For Euclidean distance

                // Calculate euclidean distance between the i node and the neighbor
                distance = EuclideanDistance(data[i], data[randomNeighbors[j]]);

                // Add neighbor and distance
                Graph[i].emplace_back(randomNeighbors[j], distance);
            }
        }
    }
    return Graph;
}