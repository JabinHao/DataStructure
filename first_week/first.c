Position BinarySearch(List L, ElementType X)
{
    Position head = 1, end = L->Last;
    Position p = (head + L->Last) / 2;
    Position result = NotFound;
    if (X < L->Data[1] || X > L->Data[L->Last])
        return result;
    while (p > head && p < end)
    {
        if (head == p && end == p)
            return NotFound;
        else if (X == L->Data[head])
            return head;
        else if (X == L->Data[end])
            return end;
        else if (X < L->Data[p])
        {
            end = p;
            p = (head + p) / 2;
            head += 1;
        }
        else if (X > L->Data[p])
        {
            head = p;
            p = (end + p) / 2;
            end -= 1;
        }
        else if (X == L->Data[p])
            return p;
        else
            return NotFound;
    }
    if (p <= head || p >= end)
        return NotFound;
}