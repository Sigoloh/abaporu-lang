#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <fstream>
#include "./EasyBMP_1.06/EasyBMP.cpp"

using namespace std;

class Image_Creation {
    private:
        vector<string> abapl_pixels;
        int scale_factor;
        char* output_path;

        template<typename T2, typename T1>
        inline T2 hex_to_int(const T1 &in) {
            T2 out;
            std::stringstream ss; ss << hex << in;
            ss >> out;
            return out;
        }

         struct RGB {
            int R;
            int G;
            int B;
        };

        int get_min_size(const int &vec_size){
            return ceil(sqrt(vec_size));
        }

        vector<vector<string>> make_min_matrix(const int &min_size, const vector<string> &abapl_pixels) {
            vector<vector<string>> min_matrix;
            int abapl_pixel_count = 0;
            for(int i = 0; i < min_size; i++) {
                vector<string> line;
                for(int j = 0; j < min_size; j++) {
                    const string abapl_pixel = abapl_pixel_count < abapl_pixels.size() ?
                            abapl_pixels.at(abapl_pixel_count)                       :
                            "#000000";
                    ++abapl_pixel_count;
                    line.push_back(abapl_pixel);
                }
                min_matrix.push_back(line);
            }

            return min_matrix;
        }

        vector<vector<string>> scale_up(const int &scale_factor, const vector<vector<string>>& min_matrix) {
            vector<vector<string>> scaled_matrix;
            for(int i = 0; i < min_matrix.size(); i++) {
                const vector<string> line_to_scale = min_matrix.at(i);
                vector<string> scaled_line;
                // Scale the line
                for(int k = 0; k < line_to_scale.size(); k++) {
                    for(int line_scale_count = 0; line_scale_count < scale_factor; line_scale_count++) {
                        scaled_line.push_back(line_to_scale.at(k));
                    }
                }

                // Scale the column
                for(int k = 0; k < scale_factor; k++) {
                    scaled_matrix.push_back(scaled_line);
                }
            }
            return scaled_matrix;
        }

        RGB get_rgb_from_hex(const string &hex) {
            const string r_factor = hex.substr(1, 2);
            const string g_factor = hex.substr(3, 2);
            const string b_factor = hex.substr(5, 2);

            RGB parsed_rgb{};
            parsed_rgb.R = hex_to_int<int>(r_factor);
            parsed_rgb.G = hex_to_int<int>(g_factor);
            parsed_rgb.B = hex_to_int<int>(b_factor);

           return parsed_rgb;
        }

        void create_image(const vector<vector<string>> &abapl_matrix, char* path_to_save) {
            BMP AnImage;

            const int img_size = abapl_matrix.size();

            AnImage.SetSize(img_size,img_size);

            // Set its color depth to 32-bits

            AnImage.SetBitDepth(32);

            // Set one of the pixels

            for(int i = 0; i < abapl_matrix.size(); i++) {
                for(int j = 0; j < abapl_matrix.size(); j++) {
                    RGB pixel_info = get_rgb_from_hex(abapl_matrix.at(i).at(j));
                    AnImage(j,i)->Red = pixel_info.R;
                    AnImage(j,i)->Green = pixel_info.G;
                    AnImage(j,i)->Blue = pixel_info.B;
                    AnImage(j,i)->Alpha = 0;
                }
            }

            AnImage.WriteToFile(path_to_save);
        }

    public:
        [[nodiscard]] Image_Creation(const vector<string> &pixels, const int &scale_factor, const char* output_path = "Output.bmp") {
            this->abapl_pixels = pixels;
            this->scale_factor = scale_factor;
            this->output_path = new char[strlen(output_path)];
            strcpy(this->output_path, output_path);
        };

        ~Image_Creation() {
            delete this;
        }

        // This is a copy/paste from Stack Overflow:
        // https://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer

        void create() {
            int min_size = get_min_size(this->abapl_pixels.size());

            vector<vector<string>> min_matrix = make_min_matrix(min_size, this->abapl_pixels);

            vector<vector<string>> scaled_matrix = scale_up(this->scale_factor, min_matrix);

            create_image(scaled_matrix, this->output_path);
        }
};