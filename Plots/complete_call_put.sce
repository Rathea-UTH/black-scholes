call_complete=read('../Vectors_results/call_complete.txt',-1,1)

put_complete=read('../Vectors_results/put_complete.txt',-1,1)

s=read('../Vectors_results/s_regular_values.txt',-1,1)

clf()
plot2d(s, [call_complete, put_complete], leg="complete call@complete put", style=[2 5])
xtitle("Graphs of complete calls and puts options at initial time")
xlabel("s")
ylabel("call and put values")
// save graph to a png file
// xs2png(gcf(),'plot_calls.png');
