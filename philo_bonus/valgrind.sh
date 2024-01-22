# --child-silent-after-fork=yes 
clear && make re && valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes -s ./philo 5 800 200 200
# clear && make re && ./philo 5 800 200 200 7
