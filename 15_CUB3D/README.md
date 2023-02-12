<h1 align="center">
	CUB3D
</h1>

##  Summary

A raycaster inspired by [Wolfenstein 3D](http://users.atw.hu/wolf3d/).

## To compile

Given `Makefile` which provides the common rules (all, clean, fclean, re). After compiling all of the source codes, the program file will be generated.
> make all

## To execute
> ./cub3D assets/maps/basic_map.cub

##  Screenshot
<img width="1197" alt="Screen Shot 2023-01-25 at 12 44 51 PM" src="https://user-images.githubusercontent.com/50944735/214641541-304f4837-dc52-4ac1-8e36-36d05afc7eab.png">

##  Features

1. The W, A, S, and D keys to move the point of view through the maze.
2. The left and right arrow keys to look left and right in the maze.
3. The ESC key to close the window and quit the program.
4. The program takes as a first argument a scene description file with the .cub extension
5. The .cub file must have 4 textures, RBG colors of the ceilling and the floor, and a vaild map. 
6. The map must be composed of only 6 possible characters: 0 for an empty space, 1 for a wall, and N,S,E or W for the player’s start position and spawning orientation.
7. If the .cub file is not vaild, program execution fails.

## Peer Evaluation(Code Review)

### As a Interviewee

#### Third attempt
<img width="574" alt="image" src="https://user-images.githubusercontent.com/50944735/217070550-0adb7360-2b6e-418e-8bbf-fe7a28304108.png">

#### Second attempt
<img width="567" alt="image" src="https://user-images.githubusercontent.com/50944735/217070657-a3708677-1573-4818-8934-3ce54ddd6b58.png">

#### First attempt
<img width="568" alt="image" src="https://user-images.githubusercontent.com/50944735/217070710-b5abf909-efe2-4788-bc95-1e44046c1cf9.png">

# cub3d : 레이캐스팅

## 배우는 것

- 레이캐스팅
- 삼각함수 이해 및 구현
- 렌더링 파이프라인
- 팀원과의 협업 및 의견 조율
- mlx 활용
- 맵파싱
