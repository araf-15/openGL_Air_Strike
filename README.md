This is Computer Graphics Course Lab Project, 

My project name is "Air Strike", I build this on openGL. 

Project Description:
In this game I have an aircraft, this aircraft can travel through an Environment. I write the 
code of the game like it will generate the environment over and over again with some 
stars/asteroid. My job will be to kill those astrieds by sooting missiles. I measure the position
of the asteroid and if my missile's position and asteroid position will be at the same position
then it will detect the collsion, and the I distroid that asteroid and increment the point of 
a player by 1. (N.B: There is a bug in point incrementing system, I found where is the problem is but
for now I have limited amount of time to finish the game, so here is a gap to fixed this type of problem)

Have to be work in future:
1) 1st of all I have to fixed the point incrementing bug.
2) For now I am not checking if the aircraft collied with the astoried or not, If I will give any
   option in future I will also measure it as the missile collied. If the aircraft collied with the
   asteroid then I will deceremtnt the aircraft life line and on that way the game will be finished.
   So, It can be say that my game is little bit incomplete but I belive I could fixed this in
   future.
   
 Requirements:
 1) As I used a background sound so, some settings in Code-Blocks is required. 
    Go to Settings > Compiler > Linker Settings > Other Linker Options > now wirte '-lwinmm' > Press 'Ok'
    
 Challenges:
 1) I tried to use a Sound Engine like 'irrKlang' but there are less documentation. So, I could not manage to play multiple sounds at a       time.
 2) I calculate all of the asteroid position menually and calculate the the ditection value, As a result there is a bug in score count,       but for now it is quite decent to play.
 
 Youtube Link:
 1) Air_Strike (openGL): https://www.youtube.com/watch?v=-0FaacByG4w&feature=youtu.be
 
 2) One day I made another game by Assembly Language: Name of the game was: Box_Slash_Game: If any one is intrested can click this link: https://www.youtube.com/watch?v=I4y7Hdu8PVo&t=48s
