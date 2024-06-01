import requests
import lkh

problem_str = requests.get('http://vrp.atd-lab.inf.puc-rio.br/media/com_vrp/instances/A/A-n32-k5.vrp').text
problem = lkh.LKHProblem.parse(problem_str)

solver_path = '../LKH-3.0.6/LKH'
output = lkh.solve(solver_path, problem=problem, max_trials=10, runs=10)

print(output)
