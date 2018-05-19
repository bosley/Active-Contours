# Snakes!

#### What
[Active contour - Wiki](https://en.wikipedia.org/wiki/Active_contour_model)
#### Why
Recently I decided I wanted to create a project that allowed me to interact
with QT / OpenCV to implement the edge detection algorithm Sobel. I just graduated and needed a project to take up some time while waiting for responses on job applications. Once I was able to make a [video / camera / image display](https://github.com/joshbosley/QT-Vemos) I implemented the algorithm fairly quickly ([its not that complex](https://en.wikipedia.org/wiki/Sobel_operator).)

My advisor's research was in [fractal based active contour models](https://www.researchgate.net/profile/Christopher_Smith51/publication/281864258_Anisotropic_Fractal_Snakes/links/55fc3c9308aeba1d9f3c539a/Anisotropic-Fractal-Snakes.pdf) (snakes) so I decided to take a peak at what all of the fuss was about and found [THIS](https://www.cse.unr.edu/~bebis/CS791E/Notes/DeformableContours.pdf) PDF explaining ***basic*** snakes. I thought it would be best to introduce myself SLOWLY before jumping into what he was/is doing.

# Results / Demo

***Main Window***
![MainWindow](https://github.com/joshbosley/Active-Contours/blob/master/images/screen%20shots/mainWindow.png?raw=true)

From here, video, camera, or an image can be loaded to interact with a snake.

***Parameters***
![Params](https://github.com/joshbosley/Active-Contours/blob/master/images/screen%20shots/options.png?raw=true)

Launch parameters for the program. (Max points, α, β, γ, display, etc)

***Snake Start***
![SnakeStart](https://github.com/joshbosley/Active-Contours/blob/master/images/screen%20shots/selectedPoints.png?raw=true)

To initialize the snake, some points are selected by hand before hitting start.

***Snake Result***
![Result](https://github.com/joshbosley/Active-Contours/blob/master/images/screen%20shots/snakeComplete.png?raw=true)

The final result of the run. The red squares are the point's "neighborhood" as mentioned in the PDF link above. 

The process of minimizing snake energy is shown frame-by-frame and can be seen here:

- [Demo Videos](https://github.com/joshbosley/Active-Contours/tree/master/demo-videos)


#### Last Words

This was a really interesting project that I may continue to play with. 
If you look in the code you'll see that there is some other nonsense I started to work with using a genetic algorithm to locate the best-fit snake as-well-as some code that does point-insertion based on intensity of angles found around the snake and a couple of different criteria. 

It may be a while before I get back to this, as it was planned to just be a quick project that all-in-all took a couple of weeks (Making the QT interface, sobel, decision to implement, etc, etc.)



