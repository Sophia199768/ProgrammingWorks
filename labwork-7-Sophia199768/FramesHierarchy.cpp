#include "FramesHierarchy.h"

void Frame::read(std::fstream& file_) {
    char byte;
    std::string name;
    int size;
    int size_of_frame;

    size_of_frame = (int) bit_field.field.size_of_my_frame[0] << 24;
    size = size_of_frame;
    size_of_frame = (int) bit_field.field.size_of_my_frame[1] << 16;
    size += size_of_frame;
    size_of_frame = (int) bit_field.field.size_of_my_frame[2] << 8;
    size += size_of_frame;
    size_of_frame = (int) bit_field.field.size_of_my_frame[3];
    size += size_of_frame;
    for (int j = 0; j < size; j++) {
        file_.read(&byte, 1);
        if (byte >= 32 and byte <= 126) {
            information += byte;
        }
    }
}

void UnSynchronisedTranscription::read(std::fstream& file_) {
    char byte;
    std::string name;
    int size;
    int size_of_frame;

    size_of_frame = (int) bit_field.field.size_of_my_frame[0] << 24;
    size = size_of_frame;
    size_of_frame = (int) bit_field.field.size_of_my_frame[1] << 16;
    size = size_of_frame;
    size_of_frame = (int) bit_field.field.size_of_my_frame[2] << 7;
    size += size_of_frame;
    size_of_frame = (int) bit_field.field.size_of_my_frame[3];
    size += size_of_frame;

    for (int j = 0; j < size; j++) {
        file_.read(&byte, 1);
        if (byte >= 32 and byte <= 126) {
            information += byte;
        }
    }
}

int TextFrames::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int UrlLink::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int CDIdentifier::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int EventTimingCodes::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int UnSynchronisedTranscription::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int SynchronisedTranscription::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int Comments::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int RelativeVolumeAdjustment::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int Equalisation::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int AttachedPicture::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int PlayCounter::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int Popularimeter::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int RecommendBufferSize::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int Link::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int Position::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int TermsOfUse::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int OwnershipFrame::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int EncryptionMethodRegistration::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int GroupIdentificationRegistration::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int PrivateFrame::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int SignatureFrame::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

int Seek::print() {
    std::cout << bit_field.field.name << ": " << information << '\n';
    return 0;
}

void Frame::reads() {
    std::string header;
    int size_of_file;
    char byte;

    for (int i = 0; i < 10; i++) {
        file.read(&byte, 1);
        header += byte;
        if (i == 2) {
            std::cout << header + 'v';
        }
        if (i == 3) {
            int vers;
            vers = (int) byte;
            std::cout << vers << '\n';
        }
        if (i >= 6) {
            if (i == 6) {
                size_of_file = (int) byte;
                size_of = size_of_file << 24;
            } else if (i == 7) {
                size_of_file = (int) byte << 16;
                size_of += size_of_file;
            } else if (i == 8) {
                size_of_file = (int) byte << 8;
                size_of += size_of_file;
            } else if (i == 9) {
                size_of_file = (int) byte;
                size_of += size_of_file;
            }
        }
    }
}

void choose_frame(Frame& object, bool flag) {
    if (object.bit_field.field.name[0] == 'T') {
        TextFrames obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'C') {
        Comments obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'W') {
        UrlLink obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'M' and object.bit_field.field.name[1] == 'C') {
        CDIdentifier obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'E' and object.bit_field.field.name[1] == 'T') {
        EventTimingCodes obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'S' and object.bit_field.field.name[1] == 'Y') {
        SynchronisedTranscription obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'U' and object.bit_field.field.name[2] == 'L') {
        UnSynchronisedTranscription obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'R' and object.bit_field.field.name[2] == 'A') {
        RelativeVolumeAdjustment obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'E' and object.bit_field.field.name[1] == 'Q') {
        Equalisation obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'A' and object.bit_field.field.name[1] == 'P') {
        AttachedPicture obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'P' and object.bit_field.field.name[1] == 'C') {
        PlayCounter obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'P' and object.bit_field.field.name[2] == 'P') {
        Popularimeter obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'R' and object.bit_field.field.name[1] == 'B') {
        RecommendBufferSize obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'L') {
        Link obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'P' and object.bit_field.field.name[2] == 'S') {
        Position obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'U' and object.bit_field.field.name[2] == 'E') {
        TermsOfUse obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'O') {
        OwnershipFrame obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'E' and object.bit_field.field.name[1] == 'N') {
        EncryptionMethodRegistration obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'G' and object.bit_field.field.name[1] == 'R') {
        GroupIdentificationRegistration obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'P' and object.bit_field.field.name[1] == 'R') {
        PrivateFrame obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'S' and object.bit_field.field.name[1] == 'I') {
        SignatureFrame obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    } else if (object.bit_field.field.name[0] == 'S' and object.bit_field.field.name[1] == 'E') {
        Seek obj = {object.bit_field.array, object.information};
        obj.read(object.file);
        flag ? obj.print() : 0;
    }
}

void read_frame(std::vector<std::string> &frame_name, std::string link) {
    std::string name;
    std::string information;
    bool flag = true;
    bool name_flag = false;
    Frame object = link;


    while (!object.file.eof() and flag) {

        for (int k = 0; k < frame_name.size(); k++) {
            object.file.read(object.bit_field.array, 10);
            if (object.bit_field.field.name[0] == '\0' or object.bit_field.field.name[1] == '\0' \
            or object.bit_field.field.name[2] == '\0' or object.bit_field.field.name[3] == '\0') {
                flag = false;
                break;
            }
            if (object.bit_field.field.name == frame_name[k]) {
                name_flag = true;
            }
            choose_frame(object, name_flag);
            name_flag = false;
        }

    }
}

void frame_all(std::string link) {
    Frame object = link;
    object.reads();
    while (!object.file.eof()) {
        object.file.read(object.bit_field.array, 10);
        if (object.bit_field.field.name[0] == '\0' or object.bit_field.field.name[1] == '\0' \
        or object.bit_field.field.name[2] == '\0' or object.bit_field.field.name[3] == '\0') {
            break;
        }
        choose_frame(object, true);
    }
}
