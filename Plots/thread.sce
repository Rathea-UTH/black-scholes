no_thread_times=read('../Vectors_results/Thread/classic_execution.txt',-1,1)
thread_times=read('../Vectors_results/Thread/thread_execution.txt',-1,1)

nb_pts=read('../Vectors_results/Thread/nb_points.txt',-1,1)

clf()
plot2d(nb_pts, [no_thread_times, thread_times], leg="without thread@with thread", style=[2 5])
xtitle("Graph of calculation time executions for printing complete put with and without thread")
xlabel(" N=M ")
ylabel("times (in seconds)")
// save graph to a png file
xs2png(gcf(),'plot_thread.png');
