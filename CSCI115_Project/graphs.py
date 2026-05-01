import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("project_results.csv")

df = df.sort_values(by=["n", "representation", "algorithm"])

#----------- For table ------------------------------------------------
table = df[[
    "n",
    "graph_type",
    "representation",
    "algorithm",
    "mean_ms",
    "stddev_ms"
]].copy()

table["mean_ms"] = table["mean_ms"].round(4)
table["stddev_ms"] = table["stddev_ms"].round(4)

table = table.rename(columns={
    "n": "Vertices",
    "graph_type": "Graph Type",
    "representation": "Representation",
    "algorithm": "Algorithm",
    "mean_ms": "Mean Runtime (ms)",
    "stddev_ms": "Standard Deviation (ms)"
})

print("\n========== Algorithm Performance Table ==========\n")
print(table.to_string(index=False))

table.to_csv("final_results_table.csv", index=False)

with open("final_results_table.txt", "w") as file:
    file.write(table.to_string(index=False))

# ---------- Save Formatted Table as Image ----------
fig, ax = plt.subplots(figsize=(12, 0.6 * len(table) + 1.5))
ax.axis("off")

formatted_table = table.copy()

formatted_table["Mean Runtime (ms)"] = formatted_table["Mean Runtime (ms)"].map("{:.4f}".format)
formatted_table["Standard Deviation (ms)"] = formatted_table["Standard Deviation (ms)"].map("{:.4f}".format)

table_image = ax.table(
    cellText=formatted_table.values,
    colLabels=formatted_table.columns,
    cellLoc="center",
    loc="center"
)

# ---------- Adjust Column Widths ----------
table_image.scale(2.2, 1.5)

col_widths = [0.10, 0.2, 0.18, 0.14, 0.20, 0.22]

for col, width in enumerate(col_widths):
    for row in range(len(formatted_table) + 1):  # +1 for header
        table_image[(row, col)].set_width(width)

table_image.auto_set_font_size(False)
table_image.set_fontsize(9)
table_image.scale(1, 1.5)

# Header styling
for col in range(len(formatted_table.columns)):
    cell = table_image[(0, col)]
    cell.set_text_props(weight="bold", color="white")
    cell.set_facecolor("#1f4e79")

# Alternating row colors
for row in range(1, len(formatted_table) + 1):
    for col in range(len(formatted_table.columns)):
        cell = table_image[(row, col)]
        if row % 2 == 0:
            cell.set_facecolor("#d9eaf7")
        else:
            cell.set_facecolor("#ffffff")

        cell.set_edgecolor("#666666")

plt.title(
    "Algorithm Performance Results",
    fontsize=16,
    fontweight="bold",
    pad=20
)

plt.tight_layout()
plt.savefig("final_results_table.png", dpi=300, bbox_inches="tight")
plt.show()

print("\nTable saved as:")
print("final_results_table.csv")
print("final_results_table.txt")    

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