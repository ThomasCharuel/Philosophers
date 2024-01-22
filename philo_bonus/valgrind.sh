# --child-silent-after-fork=yes 
clear && make re && valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes -s ./philo_bonus "5" "60" "60" "60" "6"
# clear && make re && ./philo_bonus 5 800 200 200 7
