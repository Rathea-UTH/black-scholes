put_complete=read('../Vectors_results/put_complete.txt',-1,1)

// just to try to superpose 2 plots
put_reduced=read('../Vectors_results/put_reduced.txt',-1,1)

s=read('../Vectors_results/s_regular_values.txt',-1,1)

clf()
plot2d(s, [put_complete, put_reduced], leg="complete put@reduced put", style=[2 5])
xtitle("Graphs of complete and reduced puts options at initial time")
xlabel("s")
ylabel("put values")
// save graph to a png file
xs2png(gcf(),'plot_puts.png');
                              
