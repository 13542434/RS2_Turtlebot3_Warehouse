### LKH CVRP CODE ###
## IMPORTANT ##
# lkh python library must be installed for this to work: https://pypi.org/project/lkh/
# pip install lkh
## How this works ##
# lkh CVRP finds best route for multiple trucks with limited capacity 
# to travel to each node until no more packages are left to take to the depot.
# There is only one depot and each truck starts and returns there.
# lkh will use as many trucks as needed for all packages to be delivered. 
# An allocations.csv file will be created with all necessary truck routes to complete the task.
# A plans.csv file is required with all distances between nodes to create a distance matrix.
# Distance matrix must be symmetric and include a node for the depot and each package.

from sklearn import manifold  # multidimensional scaling
import numpy as np
import lkh
import math

# Change as needed
CAPACITY = 2 # Number of packages each truck can hold can be adjusted as needed
plans_path = "../catkin_ws/src/turtlebot3_warehouse/include/turtlebot3_warehouse/plans.csv"
solver_path = '../LKH-3.0.6/LKH'
allocations_path = "../catkin_ws/src/turtlebot3_warehouse/include/turtlebot3_warehouse/allocations.csv"

# convert distance_matrix to a set of xyz coords
with open(plans_path) as f:
    plans = f.read() # read the set of distances from csv

# print(plans)
# Plans formatted as:

# Start,End,Distance
# Depot,Depot,0
# Depot,Package1,19.108
# Depot,Package2,15.617
# Depot,Package3,15.1911
# Package1,Depot,19.108
# Package1,Package1,0
# Package1,Package2,8.00895
# Package1,Package3,12.9176
# Package2,Depot,15.617
# Package2,Package1,8.00895
# Package2,Package2,0
# Package2,Package3,9.42828
# Package3,Depot,15.1911
# Package3,Package1,12.9176
# Package3,Package2,9.42828
# Package3,Package3,0

plans = plans.split()# splits the plans by whitespace (commas are left in each line)
# print(plans)

# determine the dimension (number of nodes including depot)
numRows = 0
for line in plans:
    numRows += 1
DIMENSION = int(math.sqrt((numRows-1))) #total rows (minus the first line) should be DIMENSION squared

dist_matrix = np.zeros((DIMENSION,DIMENSION),float) # Create an array to collect the distance data (e.g. 4x4 of floats) size depends on number of nodes (DIMENSION)

# Fill the dist_matrix with the distance data
rowCounter = -1 # skips first line (Start,End,Distance)
colCounter = 0
for line in plans:
    if rowCounter >= 0 and colCounter < DIMENSION:
        line = line.split(',') # splits the line by commas
        dist_matrix[rowCounter,colCounter] = float(line[2]) # add distance to the matrix
        colCounter += 1    
        if colCounter >= DIMENSION:
            colCounter = 0
            rowCounter += 1
    if rowCounter >= DIMENSION or rowCounter < 0:
        rowCounter = 0

# print(dist_matrix)
# Expecting a symmetric matrix:
# [[ 0.      19.108   15.617   15.1911 ]
#  [19.108    0.       8.00895 12.9176 ]
#  [15.617    8.00895  0.       9.42828]
#  [15.1911  12.9176   9.42828  0.     ]]

mds_model = manifold.MDS(n_components=3, random_state=123,
                             dissimilarity='precomputed')
mds_fit = mds_model.fit(dist_matrix)
mds_coords = mds_model.fit_transform(dist_matrix)
mds_coords = mds_coords*1000
mds_coords = mds_coords.astype(int)
# print(mds_coords)


# Convert mds_coords into the node_coord_str for the problem_str
# Example:
# [[ 1480 -8790 -7621]
#  [-1919  8530  -197]
#  [ 3518  3112  2233]
#  [-3080 -2852  5585]]

node_coord_str = ""
row = 0
while row < DIMENSION:
    nodeNum = row + 1
    line_str = str(nodeNum) + " " + str(mds_coords[row,0]) + " " + str(mds_coords[row,1]) + " " + str(mds_coords[row,2]) + "\n"
    node_coord_str += line_str
    row += 1

# print(node_coord_str)
# 1 x x x
# 2 x x x
# 3 x x x
# 4 x x x

# Set up demand_str for the problem_str
# each node has a demand of one (every node is a package)
# except for depot (node 1) which has demand 0
demand_str = ""
row = 0
while row < DIMENSION:
    nodeNum = row + 1
    if row == 0:
        line_str = str(nodeNum) + " 0\n"
    else:
        line_str = str(nodeNum) + " 1\n"
    demand_str += line_str
    row += 1

# print(demand_str)
# 1 0 --> Depot 0
# 2 x --> Package1 x
# 3 x --> Package2 x
# 4 x --> Package3 x

problem_str = """NAME : rs2
COMMENT : (Robotics Studio 2: TurtleBot Warehouse)
TYPE : CVRP
DIMENSION : """ + str(DIMENSION) + """
CAPACITY : """+ str(CAPACITY) +"""
EDGE_WEIGHT_TYPE : EUC_3D
NODE_COORD_SECTION
""" + node_coord_str + """DEMAND_SECTION
""" + demand_str + """DEPOT_SECTION
1
-1
EOF"""

# print(problem_str)
# Example:
# NAME : rs2
# COMMENT : (Robotics Studio 2: TurtleBot Warehouse)
# TYPE : CVRP
# DIMENSION : 4
# CAPACITY : 2
# EDGE_WEIGHT_TYPE : EUC_3D
# NODE_COORD_SECTION
# 1 1480 -8790 -7621
# 2 -1919 8530 -197
# 3 3518 3112 2233
# 4 -3080 -2852 5585
# DEMAND_SECTION
# 1 0
# 2 1
# 3 1
# 4 1
# DEPOT_SECTION
# 1
# -1
# EOF

# solve the problem with lkh
problem = lkh.LKHProblem.parse(problem_str)

output = lkh.solve(solver_path, problem=problem, max_trials=10, runs=10)
# print(output)
# [[x,x], [x]]

# write the output to the allocations.csv file
allocation_str = ""
line_str = ""
allocationNum = 1
for allocations in output:
    line_str = "Allocation" + str(allocationNum)
    for package in allocations:
        line_str += ",Package" + str(package-1)
    line_str += "\n"
    allocation_str += line_str
    allocationNum += 1

# print(allocation_str)
# Example:
# Allocation1,Package1,Package2
# Allocation2,Package4,Package3

with open(allocations_path,"w") as f:
    if f.writable():
        f.write(allocation_str)
    else:
        print("The file allocations.csv cannot be written to")
    f.close()

