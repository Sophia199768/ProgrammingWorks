#pragma once
#include <iostream>
#include <fstream>
#include <vector>
class Frame;

void choose_frame(Frame& object);
void frame_all(std::string link);
void read_frame(std::vector<std::string>& frame_name, std::string link);

class Frame {
    friend void choose_frame(Frame& object);

public:
    union {
        char array[10];
        class {
        public:
            char name[4];
            unsigned char size_of_my_frame[4];
            char flags_[2];
        } field;
    } bit_field;


    Frame() = default;

    Frame(std::string link) {
        file.open(link, std::ios_base::in | std::ios_base::binary);
    }
    std::string information;
    virtual void read(std::fstream& file_);
    void reads();
    std::fstream file;
    int size_of;
};

class TextFrames : public Frame {
public:

    TextFrames(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }

    int print();
};

class UrlLink : public Frame {
public:
    UrlLink(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class CDIdentifier : public Frame {
public:
    CDIdentifier(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class EventTimingCodes : public Frame {
public:
    EventTimingCodes(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class SynchronisedTranscription : public Frame {
public:
    SynchronisedTranscription(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class UnSynchronisedTranscription : public Frame {
public:
    UnSynchronisedTranscription(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    void read(std::fstream& file_);
    int print();
};

class Comments : public Frame {
public:
    Comments(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class RelativeVolumeAdjustment : public Frame {
public:
    RelativeVolumeAdjustment(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class Equalisation : public Frame {
public:
    Equalisation(char *str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class AttachedPicture : public Frame {
public:
    AttachedPicture(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class PlayCounter : public Frame {
public:
    PlayCounter(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class Popularimeter : public Frame {
public:
    Popularimeter(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class RecommendBufferSize : public Frame {
public:
    RecommendBufferSize(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class Link : public Frame {
public:
    Link(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class Position : public Frame {
public:
    Position(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class TermsOfUse : public Frame {
public:
    TermsOfUse(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class  OwnershipFrame : public Frame {
public:
    OwnershipFrame(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class EncryptionMethodRegistration : public Frame {
public:
    EncryptionMethodRegistration(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class  GroupIdentificationRegistration : public Frame {
public:
    GroupIdentificationRegistration(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class  PrivateFrame : public Frame {
public:
    PrivateFrame(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class SignatureFrame : public Frame {
public:
    SignatureFrame(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

class Seek : public Frame {
public:
    Seek(char* str, std::string inf) {
        memcpy(bit_field.array, str, 10);
        information = inf;
    }
    int print();
};

//произвольно колличество произведений делоаем таблички где совпадают поля
// csv построить есть порядка 100 произведений, надо их проанализировать
// указываем путь и в майне все делать с помощью этих функций, которые характеризуют эти mp3
// если общие то по ним и строим
