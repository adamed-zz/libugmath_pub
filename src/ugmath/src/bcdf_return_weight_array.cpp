

























struct BCDF_s;

double* BCDF_return_weight_array(struct BCDF_s* a, int* count)
{
    *count = 0;

    struct Node { double* weights; int count; };
    Node* node = *reinterpret_cast<Node**>(reinterpret_cast<char*>(a) + 8);
    if (!node)
        return nullptr;
    double* result = node->weights;
    *count = node->count;
    return result;
}
