# StarHuddle
StarHuddle is an asset manager that packages your assets into a singular packaged file.

# Links
- [ Usage ]( #usage )
- [ Build ]( #build )
- [ Libraries ]( #libraries )
- [ Overview ]( #overview )
- [ Expansion ]( #expansion )

# Usage
Just simply launch the application through the .exe. Be vigilant with closing as StarHuddle doens't save current assets importing into it ATM.

## Importing
Importing is done easily by just draging a file into the application, that includes multiple files aswell.

## Exporting
You can select assets in the grid, your selection is connected to the export button. Which then gives you the option of the location of where to store the selected assets.

## Details
Also while selecting you can notice a window on the right, this is the details panel. And showcases details about the selected asset.

## Packaging
When pressing the package button it'll prompt on the location to save the compressed archive. And it will then archive all assets currently inside of the grid to the package

# Build

StarHuddle makes use of Premake for its project building. To build the project you just simply write `premake.exe vs2022` to build it for Visual Studio 2022.

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

# Expansion

While the basic functionality for an asset manager is there, if the developer whishes to expand the format support they can do so by follow these steps ( Unfortunatly it's very convoluted, as i couldn't implement better Asset abstraction due to time contraints )

### File Formats

Adding new file formats to StarHuddle is an easy step.

Mainly you need to add a new class, that inherits and integrates method from the Asset class

Other than that you need the affect a other places to enable full support in the tool.

- PackageUtil.h

In the PackageHeader you need to add onto the Header struct a `uint32_t` counter to hold asset count.

```
struct PackageHeader
{
    uint32_t json_count;
    uint32_t tga_count;
    uint32_t ogg_count;
    uint32_t X;
    uint32_t package_size;
    uint32_t compressed_size;
};
```
X : Your new file format counter

And the package struct that holds the actuall data of each asset of your new type.

```
struct Package
{
    PackageHeader header;
    std::vector< PackageData > json;
    std::vector< PackageData > tga;
    std::vector< PackageData > ogg;
    std::vector< PackageData > X;
};
```
X : Your new file format data holder

---

- PackageUtil.cpp

There are 7 places where you need to add code for your new asset to be able to package / unpackage

1.At the marker:"Data Copying", you simply need to use the `data_copying` lambda which takes the vector you just created from the header. This lambda copies all the data into `data`

2.The next marker:"Writing Format Count" you need to add a new `FileUtil::write()` function to write the amount of assets your gonna package, which is the variable you just made in the header

3.Marker:"Writing Data Struct" is just like the first one, make use of a lambda which in this case is `data_writing`. It takes the vector of PackagedData and writes out the header information.

4.Now we are at the reading stage, at marker:"Reading Format Count". Here you simply add a read function `FileUtil::read()` which will data into the asset count.

5.At marker:"Reading Data Headers" we are gonna read the header information of the packaged data using the lambda `data_header_reading`, which takes the count of the asset type

6.Marker:"Reading Data" uses the lambda `data_reading` which will read the data that we just decompressed, and put it into the correct place, which is the parameter you give( data vector )

7.Lastly we finally import the asset we just loaded with by looping through all the assets per type, and importing it into the AssetManager. Which is simplified through the lambda `import_asset`

---

- TopBar.cpp

For the TopBar.cpp you need to affect 2 places.

1.The first one is for packaging the actual data into the combined format.
Which you can find on the "File Format Combination" Mark in the .cpp

There you need to add a seperate `else if` statement for adding up your new file format, like so:

```
else if( asset_value->getType() == Asset::Type::X )
{
    package.XX.push_back( { asset_value->getData(), asset_value->getDataSize(), asset_value->getName() } );
    package.header.XXX += 1;
}	
```
X   : Your new file format type.
XX  : The vector you added in `Package.h`.
XXX : The counter you added in `Package.h`.

---

2.The second one is for exporting the individual asset onto the desktop. Which you can find at the "File Format Exporting" Marker in the .cpp

Just like before you need to add a `else if` statement for your new file format:

```
else if( asset->getType() == Asset::Type::X )
{
    filter_spec.pszName = L"XX";
    filter_spec.pszSpec = L"*.XXX";
    extension           = L"XXX";
}
```
- X   : Being your new file format.
- XX  : The expanded extension name
- XXX : Is the extension name / to what file type it saves

---

- AssetManager

The 3 asset manager changes are all one-liners so their here are some quick and easy templates.

At marker:"File Importing" you can make use of this template.
The template creates a new instance of an asset using a shared_ptr to not have dangling asset pointers

```
else if( extension == std::string( ".X" ) )
    m_assets.emplace( m_next_id, std::make_shared< XX >( m_next_id++, name, extension, payload.data, payload.data_size ) );
```
- X: the extension of the file format
- XX: Actual class you added for the new file format

---

At marker:"Asset Importing" you can make use of this template.
Same as above, the template creates a shared_ptr asset for better memory maintenence

```
case Asset::Type::X:  m_assets.emplace( m_next_id, std::make_shared< XX >( m_next_id++, _package_data.name, "XXX", static_cast< uint8_t* >( _package_data.data ), _package_data.size ) ); break;

```
- X: The type of the new format
- XX: Actual class you added for the new file format
- XXX: the extension of the file format

---