#include "imagechanger.h"
#include "Detector.h"
#include "Classificator.h"

class Anonimus {
public:
    Anonimus         (const std::string& video_path, Detector* detector, ImageChanger* changer = new ImageChanger());
    Anonimus         (int camera, Detector* detector, ImageChanger* changer = new ImageChanger());
    Anonimus         (int camera, Detector* detector, Classificator* classificator, ImageChanger* changer = new ImageChanger());
    Anonimus         ();
    ~Anonimus        ();

    void setVideo    (const std::string& video_path);
    void setVideo    (int camera);
    void addNewObj   (const cv::Mat& faceFrame);

    void setDetector (Detector* detector);
    void setChanger  (ImageChanger* changer);
    void setClassificator(Classificator* classificator);

    bool join        (int delay = 1);
    bool joinTrack   (int delay = 1);
private:
    Detector*        detector;
    ImageChanger*    changer;
    Classificator*   classificator;
    cv::VideoCapture cap;
};
