put_complete=read('../Vectors_results/put_complete.txt',-1,1)

s=read('../Vectors_results/s_regular_values.txt',-1,1)

clf()
plot2d(s, [put_complete], leg="complete put", style=[2])
xtitle("Graph of complete put options at initial time")
xlabel("s regular")
ylabel("complete put values")
// save graph to a png file
xs2png(gcf(),'plot_test.png');
