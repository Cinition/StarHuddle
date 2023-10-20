# StarHuddle
Starhuddle is an asset manager that packages your assets into a singular packaged file.

# Links
- [ Usage ]( #usage )
- [ Build ]( #build )
- [ Libraries ]( #libraries )
- [ Overview ]( #overview )

# Usage
Just simply launch the application through the .exe. Be vigilant with closing as Starhuddle doens't save current assets importing into it ATM.

## Importing
Importing is done easily by just draging a file into the application, that includes multiple files aswell.

## Exporting
You can select assets in the grid, your selection is connected to the export button. Which then gives you the option of the location of where to store the selected assets.

## Details
Also while selecting you can notice a window on the right, this is the details panel. And showcases details about the selected asset.

## Packaging
When pressing the package button it'll prompt on the location to save the compressed archive. And it will then archive all assets currently inside of the grid to the package

# Build

Starhuddle makes use of Premake for its project building. To build the project you just simply write `premake.exe vs2022` to build it for Visual Studio 2022.

Go to [this link](https://premake.github.io/docs/Using-Premake) more information on how to build to other platforms

# Libraries

### Raylib | A game development framework 

A game making framework, that simplifies rendering down so that the developer can focus on the ensential features of what they want to achieve.

I chose this framework mostly out of wanting a challenge and to showcase my UI programming skill, as Raylib doesn't implement UI elements out of the gate

### Zstd | the compression library

Zstandard is the most prevelent compression library that has a large development usage in all fields.

And thats mainly the reason why i chose it aswell, as i wanted to get as much help as i could get. As i've never dabled in compression.

### nlohmann | Json handling library

Nlohmann json is the standard of json libraries in my eyes, as there is a good base layer for json manipulation. But also has a layer for tooling function that simplifiy that manipulation further

# Overview

I had alot of fun with this code test, as it felt like a good scoped project that i then made overscoped, as find UI programming endessly enjoyable. Thus i used a barebone framework to handle the rendering and did all the UI elements myself.

Everything went well and according to my planning, i was meeting my daily deadlines until i had to start with Files/Folder and Compression

I've done some file manipulation for windows before, but that was with an outdated library and thus very different from what i used in this project.

But the compression is something i need to get a better grasp of. As there isn't that much documentation out there for them, you need to delve into it's depths. Which excites me but also let's me down as i didn't grasp this knowledge during these 2 weeks.