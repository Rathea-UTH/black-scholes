call_complete=read('../Vectors_results/call_complete.txt',-1,1)

// just to try to superpose 2 plots
call_reduced=read('../Vectors_results/call_reduced.txt',-1,1)

s=read('../Vectors_results/s_regular_values.txt',-1,1)

clf()
plot2d(s, [call_complete, call_reduced], leg="complete call@reduced call", style=[2 5])
xtitle("Graphs of complete and reduced calls options at initial time")
xlabel("s")
ylabel("call values")
// save graph to a png file
xs2png(gcf(),'plot_calls.png');
