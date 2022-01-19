#include <iostream>
#include <vector>

using namespace std;

//struct Image {
//    double quality;
//    double freshness;
//    double rating;
//};
//
//struct Params {
//    double a;
//    double b;
//    double c;
//};

class FunctionPart{
public:
    FunctionPart(char new_operation, double new_value){
        operation = new_operation;
        value = new_value;
    }

    double Apply(double source) const {
        if (operation == '+'){
            return source + value;
        } else if (operation == '-'){
            return source - value;
        } else if (operation == '*'){
            return source * value;
        } else {
            return source / value;
        }
    }

    void Invert(){
        if (operation == '+'){
            operation = '-';
        } else if (operation == '-'){
            operation = '+';
        } else if (operation == '*'){
            operation = '/';
        } else {
            operation = '*';
        }
    }

private:
    char operation;
    double value;
};

class Function{
public:
    void AddPart(char operation, double value){
        function_parts.push_back({operation, value});
    }

    double Apply(double value) const {
        for (const auto &part : function_parts){
            value = part.Apply(value);
        }
        return value;
    }

    void Invert(){
        for (auto &part : function_parts){
            part.Invert();
        }
        reverse(function_parts.begin(), function_parts.end());
    }

private:
    vector<FunctionPart> function_parts;
};

//Function MakeWeightFunction(const Params& params,
//                            const Image& image) {
//    Function function;
//    function.AddPart('*', params.a);
//    function.AddPart('-', image.freshness * params.b);
//    function.AddPart('+', image.rating * params.c);
//    return function;
//}
//
//double ComputeImageWeight(const Params& params, const Image& image) {
//    Function function = MakeWeightFunction(params, image);
//    return function.Apply(image.quality);
//}
//
//double ComputeQualityByWeight(const Params& params,
//                              const Image& image,
//                              double weight) {
//    Function function = MakeWeightFunction(params, image);
//    function.Invert();
//    return function.Apply(weight);
//}

//int main() {
//    Image image = {10, 2, 6};
//    Params params = {4, 2, 6};
//    cout << ComputeImageWeight(params, image) << endl;
//    cout << ComputeQualityByWeight(params, image, 52) << endl;
//    return 0;
//}
