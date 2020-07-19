Developers' Reference {#developer_reference}
================
<ul>
<li><a href="#Programming Reference">Programming Reference</a>
<li><a href="#High-Level Design">High-Level Design</a>
<li><a href="#Coding Style">Coding Style</a>
<li><a href="#Common Tasks">Common Tasks</a>
</ul>
### <a name = "Programming Reference"> Programming Reference</a>
For detailed codes for image_editor library and Flashphoto and Mia applications, please refer to: [click here] (file:///home/yanxx576/3081/3081_F18/repo-yanxx576/PROJ/web/doxygen-html/annotated.html)
### <a name = "High-Level Design"> High-Level Design</a>
For this project, we created an imagetools library that is implemented by two applications - Flashphoto and Mia.
![General Structure UML](resources/generaluml.png)
Within the imagetools library, we designed 8 digital painting tools and 8 imaging editing filters. Images are stored within [pixels](file:///home/yanxx576/3081/3081_F18/repo-yanxx576/PROJ/web/doxygen-html/classimage__tools_1_1PixelBuffer.html) via [ColorData](file:///home/yanxx576/3081/3081_F18/repo-yanxx576/PROJ/web/doxygen-html/classimage__tools_1_1ColorData.html). To design tools, we designed the [Tool](file:///home/yanxx576/3081/3081_F18/repo-yanxx576/PROJ/web/doxygen-html/classimage__tools_1_1Tool.html) class on an abstract level, as all tools run in similar patterns yet each have a specific characteristic. For [Filter](file:///home/yanxx576/3081/3081_F18/repo-yanxx576/PROJ/web/doxygen-html/classimage__tools_1_1Filter.html), we grouped filters into simple filters and convolution filters based on if they are convolution-based.

We implemented model-view-controller method that divided application into three interconnected parts. We seperated internal representations of information, image_tools, from the ways information is presented to and accepted from the user, mia and flashphoto.

We implemented template method and created a skeleton for running filters. For simple filters, we loop through the image stored in a 2D array and change image data according to filter's design. For [convolution filters](file:///home/yanxx576/3081/3081_F18/repo-yanxx576/PROJ/web/doxygen-html/classimage__tools_1_1ConvolutionFilter.html), we use a 2D filter matrix, named kernel. For every pixel within the image, multiply the kernel with 2D image data centered at the pixel.
![Filter Class UML](resources/filteruml.png)
For tools, the base class Tool is abstract, and the ImageEditor is not aware which tool is called when adding stroke to canvas. Detailed implementation will be determined at runtime.

Flashphoto is a GUI interface that allows us to edit images using tools and filters from imagetools library. Also, we are able to load and save files through this interface.
![Flashphoto Interface](resources/flashphotoGUI.png)
Mia has two modes - a GUI mode and a command mode. Since it was designed for medical application, within Mia's GUI mode, it only implements stamp and pen tools yet all filters are still available. 
![Mia Gui](resources/miaGUI.png)
Mia can also be used through a command mode, where all filters can be called. This mode is implemented by [ImageEditorCommand](file:///home/yanxx576/3081/3081_F18/repo-yanxx576/PROJ/web/doxygen-htm).
### <a name = "Coding Style"> Coding Style</a>
For code design, we adapted Google Style criterion. For further reference of Google Style, please [click here](https://google.github.io/styleguide/cppguide.html).

We used cpplint, a static code checker for C++, to ensure we conform to Google Style coding guide.

We used white spaces for indentation. We used ' _ ' as variables' word seperator(e.g.: pixel_buffer_) and capitalization for methods' word seperator(e.g.: ApplyBlurFilter()). And we named our variables and methods with an emphasize on readability.

We used namespace image_tools for all designs.
### <a name = "Common Tasks"> Common Tasks
To add a filter to our project. You firstly need to determine if it were a simple filter or a convolution filter.

If the new filter were a simple filter, it can be directly inherited fome [Filter](file:///home/yanxx576/3081/3081_F18/repo-yanxx576/PROJ/web/doxygen-html/classimage__tools_1_1Filter.html) class and overrides CalculateFilterPixel() method based on this filter's implementation.

If the new filter were a convolution filter, it needs to be inherited from [ConvolutionFilter](file:///home/yanxx576/3081/3081_F18/repo-yanxx576/PROJ/web/doxygen-html/classimage__tools_1_1ConvolutionFilter.html) class and overrides CreateKernel() method.
