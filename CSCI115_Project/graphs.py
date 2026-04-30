import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("algorithmDataLab05.csv")

cases = df["case"].unique()

for case in cases:
    plt.figure()
    case_data = df[df["case"] == case]
    algorithms = case_data["algorithm"].unique()
    
    for alg in algorithms:
        alge_data = case_data[case_data["algorithm"] == alg]
        alge_data = alge_data.sort_values("size")
        plt.plot(alge_data["size"], alge_data["time_ms"], marker = 'o',label = alg)

    plt.xscale("log")
    plt.yscale("log")
    plt.xlabel("input size")
    plt.ylabel("time (ms)")
    plt.title(f"Sorting Algorithm performance - {case}")
    plt.legend()
    plt.tight_layout()
    plt.show()