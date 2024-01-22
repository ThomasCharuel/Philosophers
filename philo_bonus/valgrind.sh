# --child-silent-after-fork=yes 
clear && make re && valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes -s ./philo_bonus 1 800 200 200 1
# clear && make re && ./philo_bonus 5 800 200 200 7
