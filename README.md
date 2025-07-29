## K-Nearest Neighbour Search project

### Part 1 - Nearest Neighbour Search

To compile: ```make```  
To run: ```make run```   
To run using valgrind: ```make val```  
To clean all: ```make clean```  

To compile using Test Main: ```make test=yes```   
To run with Test Main: ```make test=yes run```  
To run Test Main using valgrind: ```make test=yes val```   
To clean Test Main all: ```make test=yes clean```   
   
Construction of Vamana graph index, implementation of GreedySearch and RobustPrune algorithms, finding the medoid of graph using brute force algorithm.

### Part 2 - Approximate Nearest Neighbours Search (with Filters) - Filtered ANNS

To compile: ```make```  

To run using default arguments: ```make run```  
To run and save output: ```make save```  
To run using custom arguments: ```make run ARGS="../dataset.bin ../queries.bin <a> <t> <L> <R> <k> <L_smal> <R_small> <R_stitched> groundtruth.txt"```  
To run and save output using custom arguments: ```make save ARGS="../dataset.bin ../queries.bin <a> <t> <L> <R> <k> <L_smal> <R_small> <R_stitched> groundtruth.txt"```   

To run using Valgrind: ```make val```  
To clean all: ```make clean```  

To compile using Test Main: ```make test=yes```    
To run with Test Main: ```make test=yes run```  
To run Test Main using valgrind: ```make test=yes val```   
To clean Test Main all: ```make test=yes clean```     


Construction of a graph index with two modes Filtered Vamana and Stitched Vamana, implementation of FilteredGreedySearch and FilteredRobustPrune algorithms, 
finding start node (medoid for each filter) using FindMedoid algorithm.  
Datasets have only one filter on each element/node (Datasets, before being used, are "cleaned" from timestamps. Also queries involving timestamps are removed). 

A ```groundtruth.h``` file has also been implemented that contains the function for generating a groundtruth.txt file (using  brute force) containing the 100 real nearest neighbors for each query point. (groundtruth.txt file is used to check and find the recall)

Also, there is a timer to count the total execution time of the program and two separate timers to count for the creation of Filtered Vamana graph and Stitched Vamana graph as well.

### Part 3 - Optimizations

A program that runs in separate phases.

#### Main Program

To compile: ```make```  

To run Groundtruth phase using default arguments: ```make run-groundtruth```  
To run Filtered Vamana phase using default arguments: ```make run-filtered```   
To run Stitched Vamana phase using default arguments: ```make run-stitched```   
To run Greedy for queries phase using default arguments: ```make run-greedy```  
To run all phases using default arguments: ```make run-all```   

To run Greedy for queries phase and save recall: ```make save-greedy```   

To run Groundtruth phase under Valgrind: ```make val-groundtruth```  
To run Filtered Vamana phase under Valgrind: ```make val-filtered```   
To run Stitched Vamana phase under Valgrind: ```make val-stitched```   
To run Greedy for queries phase under Valgrind: ```make val-greedy```  
To run all phases under Valgrind: ```make val-all```   

#### Test Main Program

To run with Test Main: ```make run-test```  
To run with Test Main under Valgrind:  ```make val-test``` 

To clean all: ```make clean``` (cleans all files - including main.o and test.o)  
To view available commands: ```make help```

* For **custom arguments** use the same commands as above, just add the new value to the argument you want to change.    
e.g. ```make run-filtered t=20 a=1.1```   
This command runs Filtered Vamana phase and changes only the value of **a** and **t** with the custom values. (the order of custom arguments does not matter)


**CONTRIBUTORS**  
[Christina Diamanti](https://github.com/ChristinaDiam)   
[Marianna Stamati](https://github.com/mariannastamati)  
[Andreas Jevtovic](https://github.com/zodicx)
