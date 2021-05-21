clc; clear all; close all; 

L1 = 9.626;
L2 = 23.5;
L3 = 18.475;
L4 = 9;
phi = 90;

x = 15;
y = 0;
z = 5;

%Theta 1
th1 = atan2d(y,x);

%Theta 2
r = sqrt(x^2+y^2);
CD = sqrt(r^2+(z-L1)^2)/2;
alpha = atan2d((z-L1),r);

th2_1 = acosd(CD)+alpha;
th2_2 = -acosd(CD)+alpha;

%Theta 3
th3_1 = atan2d((z-L1-sind(th2_1)),(r-cosd(th2_1)))-th2_1;
th3_2 = atan2d((z-L1-sind(th2_2)),(r-cosd(th2_2)))-th2_2;

%Theta 4
th4_1 = phi - th2_1 - th3_1;
th4_2 = phi - th2_2 - th3_2;

