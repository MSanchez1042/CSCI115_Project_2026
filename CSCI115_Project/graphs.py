import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("project_results.csv")

# ---------- Bar Chart: Mean Runtime with Standard Deviation ----------

df["label"] = (
    df["representation"] + "\n" +
    df["algorithm"] + "\n" +
    "n=" + df["n"].astype(str)
)

plt.figure(figsize=(12, 6))

plt.bar(
    df["label"],
    df["mean_ms"],
    yerr=df["stddev_ms"],
    capsize=5
)

plt.ylabel("Mean Runtime (ms)")
plt.xlabel("Graph Representation / Algorithm / Size")
plt.title("Algorithm Runtime with Standard Deviation")
plt.xticks(rotation=45, ha="right")
plt.tight_layout()
plt.savefig("runtime_bar_chart.png", dpi=300)
plt.show()


# ---------- Line Chart: Runtime Growth ----------

groups = df.groupby(["representation", "algorithm", "graph_type"])

plt.figure(figsize=(10, 6))

for name, group in groups:
    group = group.sort_values("n")

    label = f"{name[0]} - {name[1]}"

    plt.errorbar(
        group["n"],
        group["mean_ms"],
        yerr=group["stddev_ms"],
        marker="o",
        capsize=5,
        label=label
    )

plt.xlabel("Number of Vertices")
plt.ylabel("Mean Runtime (ms)")
plt.title("Runtime Growth by Algorithm and Graph Representation")
plt.legend()
plt.tight_layout()
plt.savefig("runtime_growth.png", dpi=300)
plt.show()