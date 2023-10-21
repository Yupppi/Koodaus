import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import csv
import plotly.graph_objects as go


# Ask for data, open the file and read the data

# measurefile = "measures.csv"
user_file = input('Enter the filename with measurement data for the part: ')
try:
    filehandle = open(user_file, encoding="utf-8-sig")
except FileNotFoundError:
    print(f'The file {user_file} could not be found.')

csv_reader = csv.reader(filehandle)
csv_header = next(csv_reader)
csv_reader = csv.reader(filehandle, quoting=csv.QUOTE_NONNUMERIC)

measurements = []
for row in csv_reader:
    measurements.append(row)

filehandle.close()

#################################################################################

# Ask for part specs and do calculations

# designMeasure = 451.5
designMeasure = float(input('Enter the design measurement for the part: '))
# upTol = 0.3
upTol = float(input('Enter the upper tolerance limit for the part: '))
# lowTol = -0.2
lowTol = float(input('Enter the lower tolerance limit for the part: '))

avg_measure = np.mean(measurements)
stddev_measure = np.std(measurements)

cpkU = ((designMeasure + upTol) - avg_measure)/(3*stddev_measure)
cpkL = (avg_measure - (designMeasure + lowTol))/(3*stddev_measure)
cp = (upTol-lowTol)/(6*stddev_measure)

measure_list = list(np.concatenate(measurements))
defectiveCount = sum(1 for i in measure_list if i > (designMeasure + upTol))
defectiveCount += sum(1 for i in measure_list if i < (designMeasure + lowTol))

print(f'\nThe mean average of measures is {round(avg_measure,2)}.')
print(f'The standard deviation of measures is {round(stddev_measure,2)}.')
print(f'The upper Cpk is {round(cpkU,3)}.')
print(f'The lower Cpk is {round(cpkL,2)}.')
print(f'The Cp is {round(cp,2)}.')
print(f'The number of parts outside tolerance range is {defectiveCount}\n')

xtitles = ['Part 1', 'Part 2', 'Part 3', 'Part 4', 'Part 5', 'Part 6', 'Part 7', 'Part 8']

designUp = designMeasure + upTol
designLow = designMeasure + lowTol
designGoal = []
designUpPlot = []
designLowPlot = []
for i in range(8):
    designGoal.append(designMeasure)
    designUpPlot.append(designUp)
    designLowPlot.append(designLow)

#################################################################
# Plot the measurements etc

fig = go.Figure()

fig.add_trace(
    go.Bar(
        x=xtitles,
        y=measure_list,
        name='Part measurements',
        marker=dict(line=dict(color='#0000ff'))
    ))

fig.add_trace(
    go.Scatter(
        x=xtitles,
        y=designGoal,
        name='Design measure',
        line_color="#ff0000"   
    ))

fig.add_trace(
    go.Scatter(
        x=xtitles,
        y=designUpPlot,
        name='High tolerance limit',
        line=dict(dash='dot'),
        line_color="#000000"
    ))

fig.add_trace(
    go.Scatter(
        x=xtitles,
        y=designLowPlot,
        name='Low tolerance limit',
        line=dict(dash='dot'),
        line_color="#000000"
    ))
# fig.update_traces(line_color="#ff0000", selector=dict(type='scatter'))
fig.update_yaxes(minor_ticks="inside")
fig.update_layout(yaxis_range=[445, 455])

fig.show()
# fig = px.line(x=x, y=designMeasure)
# plt.plot(designMeasure, color='red')
# plt.title("Measurements of the manufactured parts")
# plt.minorticks_on()
# plt.tick_params(axis='x', which='minor', bottom=False)
# plt.tick_params(axis='x', which='both', bottom=False)
# plt.ylabel("Measure (cm)")
# plt.xlabel("Part")
# plt.bar(xtitles, measure_list, color='orange')
# plt.ylim(445, 455)
# plt.show()
# 