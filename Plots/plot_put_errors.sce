put_errors=read('../Vectors_results/put_errors.txt',-1,1)

// complete => pas régulier pour s
s_regular=read('../Vectors_results/s_regular_values.txt',-1,1)

clf()
plot(s_regular, put_errors, leg="absolute errors between complete and reduced puts", style=[2])
xtitle("Graph of the absolute errors between complete and reduced puts at initial time")
xlabel("s")
ylabel("errors values")
// save graph to a png file
xs2png(gcf(),'plot_put_errors.png');