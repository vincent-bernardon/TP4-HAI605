#include <filesystem>
#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;

void convertToPng(const fs::path& path) {
    cv::Mat img = cv::imread(path.string(), cv::IMREAD_UNCHANGED);
    std::string pngPath = "png/" + path.stem().string() + ".png";
    cv::imwrite(pngPath, img);
}

int main() {
    fs::path projectPath = "/chemin/vers/votre/projet"; // Remplacez par le chemin de votre projet
    fs::path pngPath = "png";

    // Créer le dossier png s'il n'existe pas
    if (!fs::exists(pngPath)) {
        fs::create_directory(pngPath);
    }

    for (const auto& entry : fs::recursive_directory_iterator(projectPath)) {
        if (entry.path().parent_path().filename() == "image") {
            continue;
        }

        if (entry.path().extension() == ".pgm" || entry.path().extension() == ".ppm") {
            convertToPng(entry.path());
        }
    }

    return 0;
}