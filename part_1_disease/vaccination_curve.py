import os
import pandas as pd
import matplotlib.pyplot as plt

report_dir = "../report_data"
vaccination_rates = [round(i * 0.1, 1) for i in range(11)]
recovered_values = []

for rate in vaccination_rates:
    filename = f"disease_stats_{rate:.1f}.csv"
    filepath = os.path.join(report_dir, filename)

    try:
        df = pd.read_csv(filepath)
        recovered = df[df["key"] == "recovered_persons"]["value"].astype(int).values[0]
        recovered_values.append(recovered)
    except Exception as e:
        print(f"⚠ Error reading {filename}: {e}")
        recovered_values.append(0)


plt.figure(figsize=(10, 6))
plt.plot([r * 100 for r in vaccination_rates], recovered_values, marker='o', linestyle='None')
plt.xlabel("vaccination_rate")
plt.ylabel("recovered")
plt.title("Recovered vs. Vaccination Rate")
plt.grid(True)
plt.tight_layout()
plt.savefig("report_data/recovered_vs_vaccination.png")
plt.show()