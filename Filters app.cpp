
#include<bits/stdc++.h>
#include "Image_Class.h"
#include <fstream>
using namespace std;


bool hasImageExtension(string &file_name) { // this function check that at the end of the string the user have added any type of image extensions
    size_t pos = file_name.find_last_of(".");
    if (pos == string::npos) {
        return false; // No period found in the string
    }
    string extension = file_name.substr(pos);
    return extension == ".jpg" || extension == ".jpeg" || extension == ".png" || extension == ".bmp";
}

void save_image(Image &image, string &original_file_name){

    string new_name;
    char user_choice;
    while (true) { // this loop will continue until the user choose how does he want to save the image
        cout << "Do you want to save the image with the same old name or a new name? (enter O for old/enter N for new): " << endl;
        cin >> user_choice; // choose one of the 2 options
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (user_choice == 'O' || user_choice == 'o') { // check that the input is o
            new_name = original_file_name; // the edited file will have the same old name
            image.saveImage(new_name);
            cout << "Image got saved successfully" << endl;
            break;
        }
        else if (user_choice == 'N' || user_choice == 'n') { // check that the input is n
            cout << "Enter the new file name for the edited image: " << endl;
            getline(cin,new_name); // take the new name from the user
            bool valid_file_name = true;
            if (new_name.length() <= 1) { // check the length of the new name
                cout << "Please enter a valid file name" << endl;
                valid_file_name = false;
            }
            if(valid_file_name && !hasImageExtension(new_name)) { // check if it contains an image extension or not
                cout << "Please enter a valid file name" << endl;
                valid_file_name = false;
            }
            if (!valid_file_name) {
                continue;
            }
            image.saveImage(new_name); // if it's correct the image will be saved
            // note that the image will be saved after the program will be terminated
            cout << "Image got saved successfully" << endl;
            break;
        }
        else { // let the user to try again
            cout << "Invalid choice. Please enter a valid letter (O or N)." << endl;
        }
    }

}


void main_menu(Image(image), string file_name);
void take_image_from_user();




// ######################################### \\
// ##############grey filter################ \\
// ######################################### \\


void grey_image(Image &image, string &original_file_name) { // grey function

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; ++j) {

            unsigned int avg = 0;   // unsigned bec when editing the pic the pixel could be out of range from 0 to 255 so unsigned prevent that

            for (int k = 0; k < 3; k++) {

                avg += image(i, j, k);
            }
            avg = avg / 3;
            for (int k = 0; k < 3; k++) {  // avg /3 to make the pic grey when all the RGB = to avg

                image(i, j, k) = avg;

            }

        }

    }

    cout << "Image is edited successfully" << endl;
    main_menu(image, original_file_name);// call menu function

}




// ################################################### \\
// ############### bright dark filter ################ \\
// ################################################### \\

void bright_dark_image(Image &image, string original_file_name) {
    while(true) { // will continue until the user save the image
        cout << "Choose A to to make the image darker" << endl;
        cout << "Choose B to to make the image brighter" << endl;
        char choice;
        cin >> choice;
        // for dark image
        if (choice == 'a' || choice == 'A') { // if input = a then the image will be dark by 50%
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; k++) {
                        // let the image equal to it slef minus 50% percent of the same image
                        float ans = image(i, j, k) = image(i, j, k) - (0.5 * (image(i, j, k)));
                        if (ans < 0) { // if ans is less than zero let the image = to 0
                            image(i, j, k) = 0;
                        } else { // else let the image = to ans
                            image(i, j, k) = ans;
                        }

                    }
                }
            }
            main_menu(image, original_file_name);// call menu function
            break; // then break from the loop


        } else if (choice == 'b' || choice == 'B') {// if input = a then the image will be bright by 50%

            // for bright image
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; k++) {
                        // let the image equal to it self plus 50% percent of the same image
                        float ans = image(i, j, k) + (0.5 * image(i, j, k));
                        if (ans > 255) {// if ans is less than 255 let the image = to 255
                            image(i, j, k) = 255;
                        } else {// else let the image = to ans
                            image(i, j, k) = ans;
                        }
                    }
                }
            }
            main_menu(image, original_file_name);// call menu function
            break; // then break from the loop

        } else { // let the user to try again
            cout << "Please enter a valid choice" << endl;
            continue;
        }
    }
}



// ################################################### \\
// ############### black white filter ################ \\
// ################################################### \\


void black_white(Image &image, string &original_file_name) {

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = avg;
                if (image(i, j, k) >= 125) {
                    image(i, j, k) = 255;
                } else
                    image(i, j, k) = 0;
            }
        }

    }
    cout << "Image is edited successfully" << endl;
    main_menu(image, original_file_name);// call menu function
}



// #################################################### \\
// ############### invert image filter ################ \\
// #################################################### \\



void invert_image_filter(Image &image, string &original_file_name) {


    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, 0) = 255 - image(i, j, 0);
                image(i, j, 1) = 255 - image(i, j, 1);
                image(i, j, 2) = 255 - image(i, j, 2);
            }
        }
    }
    cout << "Image is edited successfully" << endl;
    main_menu(image, original_file_name);// call menu function


}


// ############################################################### \\
// ############### flip image horizontally filter ################ \\
// ############################################################### \\



void flipHorizontally(Image& image, string &original_file_name) {
    for (int i = 0; i < image.width / 2; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                unsigned char temp = image(i, j, k);
                image(i, j, k) = image(image.width - 1 - i, j, k);
                image(image.width - 1 - i, j, k) = temp;
            }
        }
    }

    main_menu(image, original_file_name);// call menu function


}



// ############################################################# \\
// ############### flip image vertically filter ################ \\
// ############################################################# \\

void flipVertically(Image& image, string &original_file_name) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height / 2; ++j) {
            for (int k = 0; k < 3; ++k) {
                unsigned char temp = image(i, j, k);
                image(i, j, k) = image(i, image.height - 1 - j, k);
                image(i, image.height - 1 - j, k) = temp;
            }
        }
    }
    main_menu(image, original_file_name);// call menu function
}


// ########################################################## \\
// ############### Menu of flip image filter ################ \\
// ########################################################## \\


void flip_image_filter(Image &image, string &original_file_name) {

    while (true) {
        char choice;
        cout << "Choose the operation:\n" << "A) Horizontal Flip\n";
        cout << "B) Vertical Flip\n" << "Enter your choice (A/B): ";
        cin >> choice;
        try {

            if (choice == 'A' || choice == 'a') {
                flipHorizontally(image, original_file_name);
                cout << "Image flipped horizontally successfully." << endl;
                break;
            } else if (choice == 'B' || choice == 'b') {
                flipVertically(image, original_file_name);
                cout << "Image flipped vertically successfully." << endl;
                break;
            } else {
                cout << "Invalid choice. Please choose 'A' or 'B'." << endl;
                continue;
            }

        }
        catch (const exception &e) {
            cerr << "Error: " << e.what() << endl;
            continue;
        }
    }

}

// ############################################## \\
// ############### merge filter ################# \\
// ############################################## \\

Image resizeImage(Image &image_2, double target_width, double target_height) {

    double s_w = image_2.width/target_width; // ratio of width is equal to old width divided by targeted width
    double s_h = image_2.height/target_height;// ratio of height is equal to old height divided by targeted height
    Image new_image_2(target_width,target_height);//then define a new image with the targeted width and height
    for (int i = 0; i < target_width; i++) {
        for (int j = 0; j < target_height; ++j) {
            for (int k = 0; k < 3; k++) {
                new_image_2(i,j,k) = image_2(i*s_w, j*s_h,k);
                //then let the new image equal to old image's width and height multiplied by ratio of width and height
            }
        }
    }

    return new_image_2;

}

void merge_filter(Image &image_1,Image &image_2 ,string &original_file_name) {
    int image_width = image_1.width;
    int image_height = image_1.height;
    Image merge_image(image_width,image_height); // define an image that will contain the merged image
                                                                //  with width and height of the first image
    Image new_image_2 = resizeImage(image_2, image_width, image_height);
    // call the resize function for the image 2 to have the same dimensions as image 1

    for (int i = 0; i < image_width; i++) {
        for (int j = 0; j < image_height; ++j) {
            for (int k = 0; k < 3; k++) {
                merge_image(i,j,k) = (image_1(i,j,k) + new_image_2(i,j,k))/2 ;
                // merge image is equal to image1 + image2 all divided by 2
            }
        }
    }
    cout << "2 Images are edited successfully" << endl;
    main_menu(merge_image, original_file_name); // call menu function
}

// ########################################################### \\
// ############### Menu of merge image filter ################ \\
// ########################################################### \\


void merge_filter_menu(Image &image_1, string &original_name) { // merge menu to take the second image

    while(true) { // this loop will continue until the user enter a valid second image
        cout << "Please, enter the file name of the second image (jpg, jpeg, png, bmp): ";
        string file_name_2;
        getline(cin,file_name_2);
        bool valid_file_name = true;
        if (file_name_2.length() <=1) { // check if the length of string is less than or equal one let the user try again
            cout << "Please enter a valid file name" << endl;
            continue;
        }
        if (valid_file_name && !hasImageExtension(file_name_2)) { // call the function that check that the string contains an image extension or not
            cout << "Please enter a valid file name" << endl;
            valid_file_name = false;
        }
        if (!valid_file_name) { // if the user entered an invalid string
            continue;
        }
        while(true) {
            Image image_2;
            try { // check if the file name user entered is found or not
                if (!image_2.loadNewImage(file_name_2)) {
                    cout << "Failed to load image. Please enter a valid file name." << endl;
                    break;
                }
            } catch (const invalid_argument &e) {
                cout << "Failed to load image. Please enter a valid file name." << endl;
                break;
            }
            merge_filter(image_1, image_2, original_name); // call merge filter function
        }
    }
}






Image black_white(Image &image){
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg=0;
            for (int k = 0; k < 3; ++k) {
                avg+=image(i,j,k);

            }
            avg/=3;
            for (int k = 0; k < 3; ++k) {
                image(i,j,k)=avg;
                if (image(i,j,k)>=125)// check if the intensity of colour is bigger than 125 turn it to black
                {
                    image(i,j,k)=255;
                }
                else// check if the intensity of colour is less than 125 turn it to white
                    image(i,j,k)=0;
            }
        }

    }
    return image;
}

// ########################################################## \\
// ############### Detect Image Edges filter ################ \\
// ########################################################## \\


void Detect_Image_Edges(Image &image, string &original_file_name) {
    Image black_white_image = black_white(image); // turn the image to black and white first
    int threshold = 25; // threshold is used to compare and check if the pixel would be considered as edge or not
    for (int i = 0; i < black_white_image.width-1; i++) {
        for (int j = 0; j < black_white_image.height-1; ++j) {
            for (int k = 0; k < 3; k++) {
                int diff = abs(black_white_image(i, j, k) - black_white_image(i + 1, j, k)) +
                           abs(black_white_image(i, j, k) - black_white_image(i, j + 1, k));
                // diff is equal to absolute a pixel_1 minus the pixel under it plus absolute pixel_1 minus the pixel on it's right
                if (diff > threshold) { // if diff is bigger than threshold consider the pixel as an edge
                    image(i, j, k) = 0;
                } else { // if diff is less than threshold don't consider the pixel as an edge
                    image(i, j, k) = 255;
                }
            }

        }
    }
    cout << "Image is edited successfully" << endl;
    main_menu(image, original_file_name); // call menu function
}


void sunlight_filter(Image &image, string &original_file_name){

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; k++) {
                if(k == 0) { // if k = 0 this means that it's the Red pixel
                    int answer = image(i, j, k) + 30; // let a variable equal to the red pixel + 30
                    image(i, j, k) = min(answer,255); // take the minimum between the variable and 255
                }
                else if(k == 2) { // if k = 2 this means that it's the blue pixel
                    int answer = image(i, j, k) *8/10;// let a variable equal to the blue pixel * 8/10
                    image(i, j, k) = min(answer,255);// take the minimum between the variable and 255
                }
                else{ // if k = 1 this means that it's the green pixel
                    int answer = image(i, j, k) +30;// let a variable equal to the green pixel + 30
                    image(i, j, k) = min(answer,255);// take the minimum between the variable and 255
                }
            }
        }
    }
    cout << "Image is edited successfully" << endl;
    main_menu(image, original_file_name); // call menu function
}

// ##################################################### //
// ################ filter rotate (90d) ################ //
// ##################################################### //


void d90(Image &image, string &original_file_name) {

    Image filter6_d90(original_file_name);
    int newwidth = filter6_d90.height; // make the new width equal to the old height
    int newheight = filter6_d90.width; // make the new height equal to the old width
    Image newfilter6_d90(newwidth, newheight); // Create a new image with swapped dimensions
    for (int i = 0; i < newwidth; ++i) { //90d
        for (int j = 0; j < newheight; ++j) {
            for (int k = 0; k < 3; ++k) {
                newfilter6_d90(i, j, k) = filter6_d90(j, newwidth - 1 - i, k); // Swap the coordinates and set the new dimensions
            }
        }
    }
    cout << "Image is edited successfully" << endl;
    main_menu(newfilter6_d90, original_file_name); // call menu function
}


// ###################################################### //
// ################ filter rotate (270d) ################ //
// ###################################################### //


void d270(Image &image, string &original_file_name) {

    Image filter6_d270(original_file_name);
    int newwidth = filter6_d270.height; // make the new width equal to the old height
    int newheight = filter6_d270.width; // make the new height equal to the old width
    Image newfilter6_d270(newwidth, newheight); // Create a new image with swapped dimensions
    for (int i = 0; i < newwidth; ++i) { //270d
        for (int j = 0; j < newheight; ++j) {
            for (int k = 0; k < 3; ++k) {
                newfilter6_d270(i, j, k) = filter6_d270(newheight - 1 - j, i, k); // Swap the coordinates and set the new dimensions
            }
        }
    }
    cout << "Image is edited successfully" << endl;
    main_menu(newfilter6_d270, original_file_name); // call menu function
}


// ###################################################### //
// ################ filter rotate (180d) ################ //
// ###################################################### //


void d180(Image &image, string &original_file_name) {

    Image filter6_d180(original_file_name);
    int newwidth = filter6_d180.height; // make the new width equal to the old height
    int newheight = filter6_d180.width; // make the new height equal to the old width
    Image newfilter6_d180(newwidth, newheight); // Create a new image with swapped dimensions
    for (int i = 0; i < newwidth; ++i) { // 180d
        for (int j = 0; j < newheight; ++j) {
            for (int k = 0; k < 3; ++k) {
                newfilter6_d180(i, j, k) = filter6_d180(newwidth - 1 - i, newheight - 1 - j, k);  // Swap the coordinates and set the new dimensions
            }
        }
    }
    cout << "Image is edited successfully" << endl;
    main_menu(newfilter6_d180, original_file_name); // call menu function
}



// ######################################################## //
// ################ filter rotate (choose) ################ //
// ######################################################## //



void choise_rotate(Image &image, string &original_file_name){
    while (true){
        cout<<"you have three choices for this filter (rotation) : "<<endl <<"a) for 90 degree  rotation "<<endl<<"b) for 180 degree rotation"<<endl<<"c) for 270 degree rotation "<<endl<<"please enter your choose : ";
        char choose6_rotate;
        cin>>choose6_rotate;
        if(choose6_rotate =='a'||choose6_rotate=='A'){
            d90(image,original_file_name);
            break;
        }
        else if(choose6_rotate =='b'||choose6_rotate=='B'){
            d180(image,original_file_name);
            break;
        }
        else if(choose6_rotate=='c'||choose6_rotate=='C'){
            d270(image,original_file_name);
        }
        else{
            cout<<"invalid choise please enter correct choise ";
        }
    }
}

// ############################################### //
// ################ filter frame1 ################ //
// ############################################### //

void frame1(Image &image, string &original_file_name){

    Image filter9_frame1(original_file_name);
    int red=0,green=0,blue=0; char choose_frame1;// Initialize color variables to default values
    while (true){
        cout<<" in this frame you have three color option :  " << endl <<" a- the outer frame is black"<<endl << " b- the outer frame is light blue"<<endl<< "please choose your option : ";
        cin>>choose_frame1;
        if (choose_frame1=='a' || choose_frame1=='A'){
            red=0,green=0,blue=0;  // Black color
            break;
        }
        else if(choose_frame1=='b' || choose_frame1=='B'){
            blue=255,green=170; // Light blue color
            break;
        }
        else{
            cout<<"enter correct option";
        }
    }
    for (int j = 0; j < filter9_frame1.height; ++j) {
        for (int l = 0; l < 100; ++l) {
            // Apply the selected color to the left side of the image
            filter9_frame1(l, j, 0) = 255;
            filter9_frame1(l, j, 1) = 255;
            filter9_frame1(l, j, 2) = 255;
            // Apply the selected color to the right side of the image
            filter9_frame1(filter9_frame1.width - l, j, 0) = 255;
            filter9_frame1(filter9_frame1.width - l, j, 1) = 255;
            filter9_frame1(filter9_frame1.width -l, j, 2) = 255;
        }
    }
    for (int j = 0; j < filter9_frame1.width; ++j) {
        for (int l = 0; l < 100; ++l) {
            // to the top side of the image
            filter9_frame1(j, l, 0) = 255;
            filter9_frame1(j, l, 1) = 255;
            filter9_frame1(j, l, 2) = 255;
        }
    }
    for (int i = 0; i < filter9_frame1.width; ++i) {
        for (int j = 0; j < 100; ++j) {
            // to the bottom side of the image
            filter9_frame1(i, filter9_frame1.height-1-j, 0) = 255;
            filter9_frame1(i, filter9_frame1.height-1-j, 1) = 255;
            filter9_frame1(i, filter9_frame1.height-1-j, 2) = 255;
        }
    }
    cout << "Image is edited successfully" << endl;
    main_menu(filter9_frame1, original_file_name); // call menu function
}

// ############################################### //
// ################ filter frame2 ################ //
// ############################################### //


void frame2 (Image &image, string &original_file_name){

    Image filter9_frame2(original_file_name);
    int red=0,green=0,blue=0,red2=0,green2=0,blue2=0;char choose_frame2; // Initialize color variables to default values
    while (true){
        cout<<" in this frame you have three color option :  "<<endl<<" a- the outer frame is black and the inner frame is white"<< endl << " b- the outer frame is light blue and the inner frame is white"<<endl<< "please choose your option : ";
        cin>>choose_frame2;
        if(choose_frame2=='a' || choose_frame2=='A'){
            red2 = 255,green2 = 255,blue2 = 255; // White inner frame
            break;
        }
        else if(choose_frame2 =='b' || choose_frame2=='B'){
            blue=255,green=170,red2=255,green2=255,blue2=255; // Light blue outer frame, white inner frame
            break;
        }
        else{
            cout<<"enter correct option";
        }
    }
    for (int j = 0; j < filter9_frame2.height; ++j) {
        for (int l = 0; l < 100; ++l) {
            // Apply the selected color to the left side of the image
            filter9_frame2(l, j, 0) = red;
            filter9_frame2(l, j, 1) = green;
            filter9_frame2(l, j, 2) = blue;
            // Apply the selected color to the right side of the image
            filter9_frame2(filter9_frame2.width - l, j, 0) = red;
            filter9_frame2(filter9_frame2.width - l, j, 1) = green;
            filter9_frame2(filter9_frame2.width -l, j, 2) = blue;
        }
    }
    for (int j = 0; j < filter9_frame2.width; ++j) {
        for (int l = 0; l < 100; ++l) {
            // to the top side of the image
            filter9_frame2(j, l, 0) = red;
            filter9_frame2(j, l, 1) = green;
            filter9_frame2(j, l, 2) = blue;
        }
    }
    for (int i = 0; i < filter9_frame2.width; ++i) {
        for (int j = 0; j < 100; ++j) {
            // to the bottom side of the image
            filter9_frame2(i, filter9_frame2.height-1-j, 0) = red;
            filter9_frame2(i, filter9_frame2.height-1-j, 1) = green;
            filter9_frame2(i, filter9_frame2.height-1-j, 2) = blue;
        }
    }
    for(int i = 100 ; i < filter9_frame2.width-150; i++){
        for(int j = 100 ; j < 135; j++){
            // Loop through the image to apply the inner frame color
            filter9_frame2(i, j, 0) = red2;
            filter9_frame2(i, j, 1) = green2;
            filter9_frame2(i, j, 2) = blue2;
        }
    }
    for(int i = 100 ; i < 135; i++){ // Loop through the image to apply the inner frame color
        for(int j = 100 ; j < filter9_frame2.height-150; j++){
            // to the left side of the image
            filter9_frame2(i, j, 0) = red2;
            filter9_frame2(i, j, 1) = green2;
            filter9_frame2(i, j, 2) = blue2;
        }
    }
    for(int i = 100 ; i < filter9_frame2.width-100; i++){ // Loop through the image to apply the inner frame color
        for(int j = 100 ; j < 135; j++){
            // to the right side of the image
            filter9_frame2(i, filter9_frame2.height-1-j, 0) = red2;
            filter9_frame2(i, filter9_frame2.height-1-j, 1) = green2;
            filter9_frame2(i, filter9_frame2.height-1-j, 2) = blue2;
        }
    }
    for(int i = 100 ; i < filter9_frame2.height-135; i++){// Loop through the image to apply the inner frame color
        for(int j = 100 ; j < 135; j++) {
            // to the bottom side of the image
            filter9_frame2(filter9_frame2.width -1- j, i, 0) = red2;
            filter9_frame2(filter9_frame2.width -1-j, i, 1) = green2;
            filter9_frame2(filter9_frame2.width -1- j, i, 2) = blue2;
        }
    }

    for(int i = 100 ; i < filter9_frame2.width-150; i++){ // Loop through the image to apply the inner frame color
        for(int j = 150 ; j < 185; j++){ // to the inner rectangle of the image
            filter9_frame2(i, j, 0) = red2;
            filter9_frame2(i, j, 1) = green2;
            filter9_frame2(i, j, 2) = blue2;
        }
    }
    for(int i = 150 ; i < 185; i++){ // Loop through the image to apply the inner frame color
        for(int j = 100 ; j < filter9_frame2.height-150; j++){ // to the top side of the inner rectangle
            filter9_frame2(i, j, 0) = red2;
            filter9_frame2(i, j, 1) = green2;
            filter9_frame2(i, j, 2) = blue2;
        }
    }
    for(int i = 100 ; i < filter9_frame2.width-100; i++){ // Loop through the image to apply the inner frame color
        for(int j = 150 ; j < 185; j++){ // to the right side of the inner rectangle
            filter9_frame2(i, filter9_frame2.height-1-j, 0) = red2;
            filter9_frame2(i, filter9_frame2.height-1-j, 1) = green2;
            filter9_frame2(i, filter9_frame2.height-1-j, 2) = blue2;
        }
    }
    for(int i = 100 ; i < filter9_frame2.height-135; i++){ // Loop through the image to apply the inner frame colo
        for(int j = 150 ; j < 185; j++) { // to the bottom side of the inner rectangle
            filter9_frame2(filter9_frame2.width -1- j, i, 0) = red2;
            filter9_frame2(filter9_frame2.width -1- j, i, 1) = green2;
            filter9_frame2(filter9_frame2.width -1- j, i, 2) = blue2;
        }
    }

    cout << "Image is edited successfully" << endl;
    main_menu(filter9_frame2, original_file_name); // call menu function
}


// ###################################################### //
// ################ filter frame(choose) ################ //
// ###################################################### //


void choise_frame(Image &image, string &original_file_name){
    while (true){
        cout<<"there are three options in this filter "<<endl <<" a) just outer frame "<<endl <<" b) outer frame with internal decoration "<<endl << " please choose the filter you want : ";
        char choose_frame;
        cin>>choose_frame;
        if(choose_frame=='a' || choose_frame=='A'){
            frame1(image, original_file_name);
            break;
        }
        else if (choose_frame == 'b' || choose_frame=='B'){
            frame2(image, original_file_name);
            break;
        }
        else{
            cout<<" invalid choose please enter correct choice ";
        }
    }
}

// ############################################### //
// ################ filter blur ################## //
// ############################################### //

void blur(unsigned char* real_image, unsigned char* blured_image, int width, int height, int channels) {
    for (int i = 0; i < height; ++i) { // Loop through each row of the image
        for (int j = 0; j < width; ++j) { // Loop through each column of the image
            for (int k = 0; k < channels; ++k) { // Loop through each color channel of the image
                int sum = 0;
                int count = 0;
                for (int ky = -1; ky <= 25; ky++) { // Iterate over the kernel in the vertical direction
                    for (int kx = -1; kx <= 25; kx++) { // Iterate over the kernel in the horizontal direction
                        int nx = j + kx; // Calculate the new horizontal position of the pixel
                        int ny = i + ky; // Calculate the new vertical position of the pixel
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height) { // Check for border conditions to ensure we're within the image boundaries
                            int pixelIndex = (ny * width + nx) * channels + k; // Calculate the index of the pixel
                            sum += real_image[pixelIndex]; // Add the pixel value to the sum
                            count++; // Increment the count of pixels
                        }
                    }
                }
                blured_image[(i * width + j) * channels + k] = sum / count; // Calculate and store the average pixel value in the blurred image
            }
        }
    }

}
// ############################################### //
// ################ filter blur2 ################# //
// ############################################### //

//Note: filter blur is the only filter that the image must be saved in the same function after the filter is applied
//   and can not be saved like other filters by choosing the save option in the main menu
void blur2(Image &image, string &original_file_name){
    string  outputFilename;
    cout << "Enter the filename for the output image: ";
    cin >> outputFilename;
    int width1, height1, channels1;
    unsigned char *imageload = stbi_load(original_file_name.c_str(), &width1, &height1, &channels1, 0); // Load the image and get its dimensions and channels
    unsigned char *outputImage = new unsigned char[width1 * height1 * channels1]; // Allocate memory for the output image
    blur(imageload, outputImage, width1, height1, channels1); // Apply blurring to the loaded image
    if (!stbi_write_png(outputFilename.c_str(), width1, height1, channels1, outputImage, width1 * channels1)) { // Write the blurred image to the specified output filename
        cout << "Failed to save blurred image" << endl; // Display an error message if failed to save the blurred image
    } else {
        cout << "Blurred image saved successfully" << endl; // Display a success message if the blurred image is saved successfully
    }
    delete[] outputImage; // Deallocate memory for the outputimage
}



// ###################################################### //
// ################ filter night purple ################# //
// ###################################################### //


void night_purple(Image &image, string &original_file_name){

    Image filter16_purple(original_file_name);
    for (int i = 0; i < filter16_purple.width; ++i) {
        for (int j = 0; j < filter16_purple.height; ++j) {
            filter16_purple(i,j,0) = filter16_purple(i,j,0); // Keep the red channel unchanged
            filter16_purple(i,j,1) = max(0, filter16_purple(i,j,1) - 50);// Decrease the green channel value by 50, ensuring it doesn't go below 0
            filter16_purple(i,j,2) = min(255, filter16_purple(i,j,2) + 1);// Increase the blue channel value by 1, ensuring it doesn't go above 255
            }
        }

    cout << "Image is edited successfully" << endl;
    main_menu(filter16_purple, original_file_name);
}



int check(int num) {
    while (true) {
        cin >> num;
        if (cin.fail() || num < 1) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << "Invalid input. Please enter valid numeric values or make dimensions more than 1." << endl;
        } else {
            return num;
        }
    }
}


void Resize_image(Image &image, string &original_file_name){

    int x, y;
    //declare x and y
    cout << "Enter the new width: ";
    x = check(x);
    //enter x in check function to make sure that it is an intiger
    cout << "Enter the new height: ";
    y = check(y);
    //enter y in check function to make sure that it is an intiger
    // Create a new image for the resized portion
    Image resizedImage(x, y);

    // Calculate scaling factors
    double Width = static_cast<double>(image.width) / x;
    double Height = static_cast<double>(image.height) / y;

    // Resize the image
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < 3; ++k) {
                resizedImage(i, j, k) = image(i * Width, j * Height, k);
            }
        }
    }

    cout << "Image is edited successfully" << endl;
    main_menu(resizedImage, original_file_name); // call menu function

}


void crop_image(Image &image, string &original_file_name){

    int x, y, width, height;
    cout << "Enter the starting X-coordinate for cropping: ";
    x = check(x);
    cout << "Enter the starting Y-coordinate for cropping: ";
    y = check(y);
    cout << "Enter the width of the cropped region: ";
    width = check(width);
    cout << "Enter the height of the cropped region: ";
    height = check(height);

    Image croppedImage(width, height);

    // Copy pixels from the original image to the cropped image
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < 3; ++k) {
                croppedImage(i, j, k) = image(x + i, y + j, k);
            }
        }
    }

    cout << "Image is edited successfully" << endl;
    main_menu(croppedImage, original_file_name); // call menu function
}



void infrared_filter(Image &image, string &original_file_name){

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Get the original RGB values
            unsigned int red = image(i, j, 0);
            unsigned int green = image(i, j, 1);
            unsigned int blue = image(i, j, 2);

            // Set red to 255
            image(i, j, 0) = 255;
            // Invert green and blue
            image(i, j, 1) = 255 - green;
            image(i, j, 2) = 255 - blue;
        }
    }

    cout << "Image is edited successfully" << endl;
    main_menu(image, original_file_name); // call menu function
}



// ########################################## \\
// ############### Main menu ################ \\
// ########################################## \\


void main_menu(Image(image), string file_name){
    while(true) {
        // main menu
        cout << "Choose one of the following options to apply a filter: " << endl;
        cout << "A) Grey filter" << endl;
        cout << "B) Darken and Lighten Image filter" << endl;
        cout << "C) Black and White filter" << endl;
        cout << "D) Invert Image filter" << endl;
        cout << "E) Flip Image" << endl;
        cout << "F) Merge filter" << endl;
        cout << "G) Detect Image Edges filter" << endl;
        cout << "H) Sunlight filter" << endl;
        cout << "I) Rotate image filter" << endl;
        cout << "J) Frame filter" << endl;
        cout << "K) Blur filter" << endl;
        cout << "L) Night purple filter" << endl;
        cout << "M) Resizing filter" << endl;
        cout << "N) Crop filter" << endl;
        cout << "O) Infrared filter" << endl;
        cout << "X) To load a new image" << endl;
        cout << "Y) To save the image" << endl;
        cout << "Z) Exit the program" << endl;
        char choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 'A' || choice == 'a') { // if choice = 'a' call function grey image
            grey_image(image, file_name);
        }
        else if (choice == 'B' || choice == 'b') {// if choice = 'b' call function bright dark image
            bright_dark_image(image, file_name);
        }
        else if (choice == 'C' || choice == 'c') {// if choice = 'c' call function black white
            black_white(image, file_name);
        }
        else if (choice == 'D' || choice == 'd') {// if choice = 'd' call function invert image filter
            invert_image_filter(image, file_name);
        }
        else if (choice == 'E' || choice == 'e') {// if choice = 'e' call function flip image filter
            flip_image_filter(image, file_name);
        }
        else if (choice == 'F' || choice == 'f') {// if choice = 'f' call function merge filter menu
            merge_filter_menu(image, file_name);
        }
        else if (choice == 'G' || choice == 'g') {// if choice = 'g' call function detect image edges filter
            Detect_Image_Edges(image, file_name);
        }
        else if (choice == 'H' || choice == 'h') {// if choice = 'h' call function sunlight filter
            sunlight_filter(image, file_name);
        }
        else if (choice == 'I' || choice == 'i') {// if choice = 'i' call function rotate image filter menu
            choise_rotate(image, file_name);
        }
        else if (choice == 'J' || choice == 'j') {// if choice = 'j' call function frame filter menu
            choise_frame(image, file_name);
        }
        else if (choice == 'K' || choice == 'k') {// if choice = 'k' call function blur filter
            blur2(image, file_name);
        }
        else if (choice == 'L' || choice == 'l') {// if choice = 'l' call function night purple filter
            night_purple(image, file_name);
        }
        else if (choice == 'M' || choice == 'm') { // if choice = 'm' call function resize image filter
            Resize_image(image, file_name);
        }
        else if (choice == 'N' || choice == 'n') { // if choice = 'e' call function crop image filter
            crop_image(image, file_name);
        }
        else if (choice == 'O' || choice == 'o') { // if choice = 'o' call function infrared filter
            infrared_filter(image, file_name);
        }
        else if (choice == 'X' || choice == 'x') {// if choice = 'x' exit the loop to let the user enter a new image
            while(true){
                char choice_2;
                cout << "Do you want to save an image before loading a new image ? (Y for Yes and N for No)" << endl;
                cin >> choice_2;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(choice_2 == 'Y' || choice_2 == 'y'){
                    save_image(image, file_name);
                    break;
                }
                else if(choice_2 == 'N' || choice_2 == 'n'){
                    take_image_from_user();
                }
                else{
                    cout << "Invalid choice. Please enter a valid choice" << endl;
                }
            }

        }
        else if (choice == 'Y' || choice == 'y') { // if choice = 'y' let the user save the image
            save_image(image, file_name);
        }
        else if (choice == 'Z' || choice == 'z') {// if choice = 'z' terminate the program
            while(true){
                char choice_2;
                cout << "Do you want to save an image before exiting the program ? (Y for Yes and N for No)" << endl;
                cin >> choice_2;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(choice_2 == 'Y' || choice_2 == 'y'){
                    save_image(image, file_name);
                    break;
                }
                else if(choice_2 == 'N' || choice_2 == 'n'){
                    exit(0);
                }
                else{
                    cout << "Invalid choice. Please enter a valid choice" << endl;
                }
            }

        }
        else { // if the user entered a wrong input let the user try again
            cout << "Invalid choice. Please enter a valid choice" << endl;
        }
    }

}

// ########################################################################## \\
// ############### Function that take an image from the user ################ \\
// ########################################################################## \\


void take_image_from_user(){


    while (true) { // loop will continue until the user type exit
        cout << "Please, enter the file name (jpg, jpeg, png, bmp) or type 'exit' to exit the program: ";
        string file_name;
        getline(cin,file_name);
        bool valid_file_name = true;
        if (file_name == "exit") { // if user typed "exit" then terminate the program
            exit(0);
        }
        if (file_name.length() <= 1) { // check if the length of string is less than or equal one let the user try again
            cout << "Please enter a valid file name" << endl;
            continue;
        }

        if(valid_file_name && !hasImageExtension(file_name)) { // call the function that check that the string contains an image extension or not
            cout << "Please enter a valid file name" << endl;
            valid_file_name = false;
        }

        if (!valid_file_name) { // if the user entered an invalid string
            continue;
        }

        while (true) {
            Image image;
            try { // check if the file name user entered is found or not
                if (!image.loadNewImage(file_name)) {
                    cout << "Failed to load image. Please enter a valid file name." << endl;
                    break;
                }
            } catch (const std::invalid_argument& e) {
                cout << "Failed to load image. Please enter a valid file name." << endl;
                break;
            }
            main_menu(image, file_name); // call the main menu function
        }
    }

}



int main() {
    cout << "Welcome to the filter program" << endl;
    take_image_from_user(); // call this function to take an image from the user

    return 0;
}
