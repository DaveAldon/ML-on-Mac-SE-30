# How to run machine learning on a Mac SE 30 from 1989

This repo contains my work on getting a basic perceptron machine learning algorithm running on my vintage Mac SE 30. It was written in C using THINK C on System 7.1. The program contains the following features:

- A gui for the user to draw a letter or shape on a grid
- A perceptron algorithm that is trained to detect the capital letter "A"
- A console output that shows the perceptron's confidence level in detecting the letter "A" from the user's drawing

## Requirements

- A Mac SE 30 running System 7.1, or an emulator like [Mini vMac](https://www.gryphel.com/c/minivmac/)
- [THINK C 5.0.2](https://macintoshgarden.org/apps/think-c)
- I recommend reading my last post on vintage Mac development [here](https://www.grandrapidsdeveloper.com/blog/How-Were-Apps-Made-40-Years-Ago) to understand how to setup THINK C

## Layout of the project

The project consists of the following files:

- `main.c`: The main file that contains the parameters and orchestration of the gui and perceptron
- `input.c` and `input.h`: The logic and headers that contain the gui for the user to draw a letter or shape on a grid
- `recognition.c` and `recognition.h`: The logic and headers that contain the perceptron algorithm and training loop
- `weights.dat`: My pre-trained weights for the perceptron
- `Machine-Learning`: The THINK C project file

## Running the project

![](/resources/project.png)

With your project files in one folder, open `Machine-Learning` which should open in THINK C.

![](/resources/setup.png)

Make sure to add the full `ANSI` resource if it's not already there. We need the full one for this project to work. It will be in your THINK C install folder like `Development/THINK C 5.0 Folder/C Libraries/ANSI`.

Inside `main.c` you can change the highlighted code to make it train every time, or to look for the pre-trained weights.

![](/resources/retrain.png)

Press `CMD+R` to run the project. You should see a window like this:

![](/resources/grid-empty.png)

Fill out the squares into whatever shape you want by clicking on them.

![](/resources/grid-full.png)

Once you're done, hit `Enter` and the program will run the perceptron on your drawing and output the confidence level in the console.

![](/resources/results.png)

## Further Reading

I got the idea to try this out when reading about Optical Character Recognition (OCR) in these 50s-90s papers and articles:

- [The Perceptron: A Probabilistic Model for Information Storage and Organization in the Brain - 1958](https://www.ling.upenn.edu/courses/cogs501/Rosenblatt1958.pdf)
- [Developer - The Apple Technical Journal - August 1992](https://vintageapple.org/develop/pdf/develop-11_9208_August_1992.pdf) - Page 85
- [MacWorld - March 1985](https://vintageapple.org/macworld/pdf/MacWorld_8503_March_1985.pdf) - Page 67

They got me thinking about what was possible with technology back then, and I knew that it should be possible to do something simple like this on a Mac SE 30. I hope you enjoy this project and it inspires you to try taking a step back, slowing things down, and really looking at the foundations of simple technology.
