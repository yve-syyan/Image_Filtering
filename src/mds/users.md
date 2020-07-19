Users' Reference {#user_reference}
================
<ul>
<li><a href="#Flashphoto">Getting Started with FlashPhoto</a>
<li><a href="#Mia">Getting Started with Mia</a>
</ul>
##
### <a name = "Flashphoto"> Getting Started with FlashPhoto</a>
#### Tools
Flashphoto is a digital painting and image-editing tool with a graphical interface. There are two groups of image-changing tools under Flashphoto - brushes and filters.

To get started, you can choose to either upload a picture of your own using **Open** or start with an empty canvas. After finishing editing your image, you can click on **Save** to download your image to local.

![Flashphoto Interface](resources/flashphotoGUI.png)
We have 7 options for painting tools available for you to add strokes to your canvas. Each of them has effects following below diagraphs. Feel free to change the color and size or your tools!
* **Tool Pen**
![Pen](resources/correct-pen.png)
* **Tool Spray Can**
![Spray Can](resources/correct-spraycan.png)
* **Tool Chalk**
![Chalk](resources/correct-chalk.png)
* **Tool Blur**
![Blur](resources/correct-blur.png)
* **Tool Highlighter**
![Highlighter](resources/correct-highlighter.png)
* **Tool Caligraphy Pen**
![Caligraphy Pen](resources/correct-caligraphypen.png)
* **Tool Stamp**
![Tool Stamp](resources/correct-mark.png)

Also, we have an **Eraser** available for you that erases strokes from your painting tools.

#### <a name = "FilterInfo"> Filters
If you would like to edit your picture as a whole, we have designed 8 filters for you to change the color, brightness, sharpness or clarity of your pictures. There affects are demonstrated below:
![original picture](resources/in.png)
* **Blur Filter**
* As the **Blur Amount** increases, the picture become more blur.
![Blur Filter(3.0)](resources/correct-blur-3.png)
* **Motion Blur Filter**
Unlike Blur Filter, Motion Blur Filter convolves your picture with only one direction. As you increase **Blur Amount**, the picture becomes more blur.
![MotionBlur Filter(East-West, 3.0)](resources/correct-mbew-3.png)
* **Threshold Filter**
* This filter changes your image into black and white based on the threshold value you entered.
![Threshold Filter(1.0)](resources/correct-threshold-1.0.png)
* **Saturation Filter**
* This filter increases the colorfulness of your picture. The larger the entered value, the brighter the picture. When entered 0, it presents the grayscale of your picture.
![Saturation Filter(3.0)](resources/correct-saturate-3.png)
* **Channels Filter**
* This filter independently scales down or up each of color channel(red, green, blue)
![Red(3.0)](resources/correct-red-3.png)
![Green(3.0)](resources/correct-green-3.png)
![Blue(3.0)](resources/correct-blue-3.png)
* **Quantize Filter**
* This filter reduces the number of colors in the image by bining.
![Quantize Fliter(10)](resources/correct-quantize-10.png)
* **Sharpen Filter**
* This filter sharpens the image in appropriate to the number you entered.
![Sharpen Filter(3.0)](resources/correct-sharpen-3.png)
* **Edge Detect Filter**
* This filter shows the edges of shapes.
![Edge Detect](resources/correct-edge.png)
Remeber, you can always redo or undo the modifications you made to your images!
### <a name = "Mia"> Getting Started with Mia</a>
This is a medical imaging software with two modes: command mode and graphical mode.
To use the command mode, you need to enter your commands with following format:
```

mia <path/to/source/image.png> [image process commands...] <path/to/output/image.png>
```
Please note, your source and output image files can only be stored as .png or .PNG files.
> For valid command line format, please follow:
>
> -blur r:             apply a gaussian blur of radius r
>
> -edgedetect:         apply an edge detection filter
>
> -sharpen r:          apply a sharpening filter of radius r
>
> -red s:              scale the red channel by factor s
>
> -green s:            scale the green channel by factor s
>
> -blue s:             scale the blue channel by factor s
>
> -quantize n:         quantize each color channel into n bins
>
> -saturate s:         saturate colors by scale factor s
>
> -threshold c:        threshold using cutoff value c
>
> -motionblur-n-s r:   north-south motion blur with kernel radius r
>
> -motionblur-e-w r:   east-west motion blur with kernel radius r
>
> -motionblur-ne-sw r: ne-sw motion blur with kernel radius r
>
> -motionblur-nw-se r: nw-se motion blur with kernel radius r

If you need to check valid command formats, please enter
```

mia -h
```
To see the effects of each filter mentioned above, please <li><a href="#FilterInfo">click here.</a>

Also, you can use the graphical mode to edit your images. You can upload and save your images by clicking **Open** and **Save**. Feel free to use all Filters available, to see effects of filters, please  <li><a href="#FilterInfo">click here.</a>

You can also use a red mark or a red pen to edit your images.
\image html correct-mark.png "Mark"
Remeber, you can always redo or undo the modifications you made to your images!
