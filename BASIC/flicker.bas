0 rem makes the screen flicker, like on retro recipes
1 speed = 50
2 i = 0
3 poke 53280, i
4 i = i + 1
5 for j=0 to speed: next j
6 if i = 15 then 2
7 goto 3
run
