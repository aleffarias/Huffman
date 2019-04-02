plot <- read.table("plot.txt", header = TRUE) 

p -> ggplot(tree) + geom_point(aes(x = numero, y = custo_lista), color = "blue") + 
  geom_point(aes(x = numero, y = custo_árvore), color = "red") +
    xlim(c(0,5000)) + ylim(c(0,5000))