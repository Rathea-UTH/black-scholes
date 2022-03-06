call_complete=read('../Vectors_results/call_complete.txt',-1,1)

// complete => pas régulier pour s
s_regular=read('../Vectors_results/s_regular_values.txt',-1,1)

clf()
plot(s_regular, put_complete, leg="complete put", style=[2])
xtitle("Graph of complete call option at initial time")
xlabel("s")
ylabel("complete call values")
// save graph to a png file
xs2png(gcf(),'plot_call_complete.png');
