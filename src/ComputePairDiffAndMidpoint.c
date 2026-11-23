struct CoordinatePair {
    int first;
    int second;
};

void ComputePairDiffAndMidpoint(const struct CoordinatePair *source, struct CoordinatePair *dest)
{
    int second = source->second;
    int first = source->first;
    struct CoordinatePair result;
    result.first = first - second;
    result.second = (second >> 1) + (first >> 1);
    *dest = result;
}

