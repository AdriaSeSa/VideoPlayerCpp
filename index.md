# Video Player using C++ by Adrià Sellarés Salvador

Welcome! This is a small project created by a Videogame Development and Design student. I'll show you how I managed to create a Video Player using Visual Studio 2019 and C++. Notice this project may possibly not work on another OS. If you want to try running the code on iOS, keep in mind you may need to make some changes. Even so, the libraries used in this project are cross platform, so the code can be very likely transformed to work using the same libraries.

In the GitHub repository you'll find two folders, one containing an exercice and the other the solution to that exercice. If you are interested on checking the Github respoitory click [here](https://github.com/AdriaSeSa/VideoPlayerCpp).

Aside from the code, I'll also have a small essay about Video Players in videogame context, as well as an explanation on what were my reasons to choose the selected libraries and methodologies. Check the following index:

1. Market Study
2. Selected Approach
3. Possible Improvements
4. Examples
5. Exercises explanation
6. References

Making a Video Player is a hard task, and if you are a beginner programmer this may be a bit challenging for you (it was plenty of a challenge for me at least). I will try to explain what is the problem we are trying to explain, before starting the project's first chapter.

The main issue with creating a Video Player in videogames it's that it requires to decodify information on an already demanding context (video games are really demanding for the computer). So decodifying a video can affect our performance. On the other hand, decodifying a video is not an easy task. There are many ways a video can be codified, and it can be stored in a lot of formats (.mp4, .wav, .avi ...), which makes the task a lot harder. 
Of these two main issues, the second one is the only we can try to approach. Performance can hardly be improved.

## Market Study

Using Videos on videogames has been a common recurrent method to introduce a videogame narrative since a long time ago. An easy example of this is Final Fantasy VII's introduction, that had a 3 minute pre-rendered animation played at the beginning of the game to introduce us it's characters and location.

<iframe width="560" height="315" src="https://www.youtube.com/embed/JujtlsiqZ-E" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Nowadays this method is used a lot less, since animating characters and using the in-game camera can be an easier way to achieve this. Even so, there are videogames that still use videos for cutscenes, introductions and endings, so it is not an obsolete tool. However it is true that, when speaking of cutscenes, videogames have ceased to use pre-rendered videos to create them, and instead are now using the engine to do it. Here are the main reasons why:

First, and most important, it requires less space in disk. Pre-rendered videos can be very heavy, specially nowadays where the standard has a very high quality.

Second, there is not a noticable change of quality. This makes reference to two things. You can use the engine to create the cutscene with a very high quality, so there is no reason to make a pre-rendered video, and there won't be a change of graphics quality when changing between gameplay and cutscene, therefore improving player inmersion.

Third, reuse, always reuse. You can't reuse a cutscene to create another cutscene. But you can use the same elements you have in your engine to create multiple cutscenes. It is just more efficient.

So, if using video insted of enginge cutscenes is just better, why would you still want to do it? Well, you certainly can avoid it, but video has a really important advantage still: it is limitless. You can create a video with any visual style. We can see a very clear example of this in the The Witcher 3 videogame's intro. In this intro, the art used for the video could not be used inside an engine because it does not share the same art style as the game. You could charge those sprites in your game to create the ctuscene inside the engine, but you would not use them again, so they would become a waste of storage. 

<iframe width="560" height="315" src="https://www.youtube.com/embed/dd2gz6AxYoA" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

In conclusion, video is still a very optimal option if you want to create cutscene where you won't use elements of the gameplay, such as characters or locations, as used in-game. If that is not the case, you can always use an engine to run the cutscene in real time, and add inmersion to the player's experience.





## Welcome to GitHub Pages

You can use the [editor on GitHub](https://github.com/AdriaSeSa/VideoPlayerCpp/edit/gh-pages/index.md) to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run [Jekyll](https://jekyllrb.com/) to rebuild the pages in your site, from the content in your Markdown files.

### Markdown

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [Basic writing and formatting syntax](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/AdriaSeSa/VideoPlayerCpp/settings/pages). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://docs.github.com/categories/github-pages-basics/) or [contact support](https://support.github.com/contact) and we’ll help you sort it out.
