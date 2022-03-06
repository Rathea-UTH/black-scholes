call_reduced=read('../Vectors_results/call_reduced.txt',-1,1)

put_reduced=read('../Vectors_results/put_reduced.txt',-1,1)

s=read('../Vectors_results/s_regular_values.txt',-1,1)

clf()
plot2d(s, [call_reduced, put_reduced], leg="reduced call@reduced put", style=[2 5])
xtitle("Graphs of reduced calls and puts options at initial time")
xlabel("s")
ylabel("call and put values")
// save graph to a png file
// xs2png(gcf(),'plot_calls.png');
