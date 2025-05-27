import pandas as pd
import matplotlib.pyplot as plt
import os


script_dir = os.path.dirname(os.path.abspath(__file__))
results_path = os.path.join(script_dir, "report_data", "disease_details.csv")


df = pd.read_csv(results_path)
df = df[df["run"] == 1]


plt.figure(figsize=(10, 6))
plt.plot(df["day"], df["infectious"], label="infectious")
plt.plot(df["day"], df["recovered"], label="recovered")
plt.plot(df["day"], df["susceptiple"], label="susceptiple")
plt.plot(df["day"], df["vaccinated"], label="vaccinated")
plt.plot(df["day"], df["infectious"] + df["recovered"] + df["susceptiple"] + df["vaccinated"], label="totalCount")

plt.xlabel("steps")
plt.ylabel("counts")
plt.title("Simulation Graph")
plt.legend(title="status")
plt.grid(True)
plt.tight_layout()
plt.show()