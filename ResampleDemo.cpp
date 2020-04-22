#include <iostream>
#include <vector>

#include <resample.h>


/// ------------------- number sequence interpolation demo -------------------
///
/// # On the container type
///
/// I am using `std::vector` in the below to avoid having to deal with fixed
/// container lengths - makes for shorter code.
/// On an MCU, since heap fragmentation is a real thing, you want to avoid
/// dynamic memory allocation and use `std::array` instead.
/// If you don't have a standard library available, plain c-style arrays would
/// work as well, obviously: `double[]`.
/// Within the Arduino universe, you might also want to take a look at
/// [janelia-arduino/Array](https://github.com/janelia-arduino/Array).


using NumberSeq = std::vector<double>;

const std::vector<size_t> OUTPUT_SIZES{2, 8, 12, 17, 99};

const NumberSeq INPUT_SEQUENCE{2, 3, 4, 5};


auto printSequence(const NumberSeq& sequence) -> void
{
    for (const auto& value : sequence)
    {
        std::cout << value << ", ";
    }
}


auto resampleSequence(
    const NumberSeq& input,
    const size_t outputSize
) -> NumberSeq
{
    const auto inputSize = input.size();

    // avoid division by 0
    if (not inputSize)
    {
        return input;
    }

    NumberSeq output{};
    output.reserve(outputSize);

    resample(outputSize, inputSize, input, output);

    return output;
}


auto main() -> int
{
    std::cout << "Input sequence: [";
    printSequence(INPUT_SEQUENCE);
    std::cout << "]" << std::endl;

    for (const size_t outputSize : OUTPUT_SIZES)
    {
        std::cout << "Output sequence, length " << outputSize << ": [";
        printSequence(resampleSequence(INPUT_SEQUENCE, outputSize));
        std::cout << "]" << std::endl;
    }

    return 0;
}
