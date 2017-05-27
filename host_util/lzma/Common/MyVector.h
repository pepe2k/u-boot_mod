// Common/Vector.h

#ifndef __COMMON_VECTOR_H
#define __COMMON_VECTOR_H

#include "Defs.h"

class CBaseRecordVector
{
  void MoveItems(int destIndex, int srcIndex);
protected:
  int _capacity;
  int _size;
  void *_items;
  size_t _itemSize;
  
  void ReserveOnePosition();
  void InsertOneItem(int index);
  void TestIndexAndCorrectNum(int index, int &num) const
    { if (index + num > _size) num = _size - index; }
public:
  CBaseRecordVector(size_t itemSize): _capacity(0), _size(0), _items(0), _itemSize(itemSize) {}
  virtual ~CBaseRecordVector();
  void ClearAndFree();
  int Size() const { return _size; }
  bool IsEmpty() const { return (_size == 0); }
  void Reserve(int newCapacity);
  void ReserveDown();
  virtual void Delete(int index, int num = 1);
  void Clear();
  void DeleteFrom(int index);
  void DeleteBack();
};

template <class T>
class CRecordVector: public CBaseRecordVector
{
public:
  CRecordVector(): CBaseRecordVector(sizeof(T)){};
  CRecordVector(const CRecordVector &v): CBaseRecordVector(sizeof(T)) { *this = v; }
  CRecordVector& operator=(const CRecordVector &v)
  {
    Clear();
    return (*this += v);
  }
  CRecordVector& operator+=(const CRecordVector &v)
  {
    int size = v.Size();
    Reserve(Size() + size);
    for (int i = 0; i < size; i++)
      Add(v[i]);
    return *this;
  }
  int Add(T item)
  {
    ReserveOnePosition();
    ((T *)_items)[_size] = item;
    return _size++;
  }
  void Insert(int index, T item)
  {
    InsertOneItem(index);
    ((T *)_items)[index] = item;
  }
  // T* GetPointer() const { return (T*)_items; }
  // operator const T *() const { return _items; };
  const T& operator[](int index) const { return ((T *)_items)[index]; }
  T& operator[](int index) { return ((T *)_items)[index]; }
  const T& Front() const { return operator[](0); }
  T& Front() { return operator[](0); }
  const T& Back() const { return operator[](_size - 1); }
  T& Back() { return operator[](_size - 1); }

  void Swap(int i, int j)
  {
    T temp = operator[](i);
    operator[](i) = operator[](j);
    operator[](j) = temp;
  }

  int FindInSorted(const T& item) const
  {
    int left = 0, right = Size();
    while (left != right)
    {
      int mid = (left + right) / 2;
      const T& midValue = (*this)[mid];
      if (item == midValue)
        return mid;
      if (item < midValue)
        right = mid;
      else
        left = mid + 1;
    }
    return -1;
  }

  int AddToUniqueSorted(const T& item)
  {
    int left = 0, right = Size();
    while (left != right)
    {
      int mid = (left + right) / 2;
      const T& midValue = (*this)[mid];
      if (item == midValue)
        return mid;
      if (item < midValue)
        right = mid;
      else
        left = mid + 1;
    }
    Insert(right, item);
    return right;
  }

  static void SortRefDown(T* p, int k, int size, int (*compare)(const T*, const T*, void *), void *param)
  {
    T temp = p[k];
    for (;;)
    {
      int s = (k << 1);
      if (s > size)
        break;
      if (s < size && compare(p + s + 1, p + s, param) > 0)
        s++;
      if (compare(&temp, p + s, param) >= 0)
        break;
      p[k] = p[s];
      k = s;
    }
    p[k] = temp;
  }

  void Sort(int (*compare)(const T*, const T*, void *), void *param)
  {
    int size = _size;
    if (size <= 1)
      return;
    T* p = (&Front()) - 1;
    {
      int i = size / 2;
      do
        SortRefDown(p, i, size, compare, param);
      while (--i != 0);
    }
    do
    {
      T temp = p[size];
      p[size--] = p[1];
      p[1] = temp;
      SortRefDown(p, 1, size, compare, param);
    }
    while (size > 1);
  }
};

typedef CRecordVector<int> CIntVector;
typedef CRecordVector<unsigned int> CUIntVector;
typedef CRecordVector<bool> CBoolVector;
typedef CRecordVector<unsigned char> CByteVector;
typedef CRecordVector<void *> CPointerVector;

template <class T>
class CObjectVector: public CPointerVector
{
public:
  CObjectVector() {};
  ~CObjectVector() { Clear(); };
  CObjectVector(const CObjectVector &v) { *this = v; }
  CObjectVector& operator=(const CObjectVector &v)
  {
    Clear();
    return (*this += v);
  }
  CObjectVector& operator+=(const CObjectVector &v)
  {
    int size = v.Size();
    Reserve(Size() + size);
    for (int i = 0; i < size; i++)
      Add(v[i]);
    return *this;
  }
  const T& operator[](int index) const { return *((T *)CPointerVector::operator[](index)); }
  T& operator[](int index) { return *((T *)CPointerVector::operator[](index)); }
  T& Front() { return operator[](0); }
  const T& Front() const { return operator[](0); }
  T& Back() { return operator[](_size - 1); }
  const T& Back() const { return operator[](_size - 1); }
  int Add(const T& item) { return CPointerVector::Add(new T(item)); }
  void Insert(int index, const T& item) { CPointerVector::Insert(index, new T(item)); }
  virtual void Delete(int index, int num = 1)
  {
    TestIndexAndCorrectNum(index, num);
    for (int i = 0; i < num; i++)
      delete (T *)(((void **)_items)[index + i]);
    CPointerVector::Delete(index, num);
  }
  int Find(const T& item) const
  {
    for (int i = 0; i < Size(); i++)
      if (item == (*this)[i])
        return i;
    return -1;
  }
  int FindInSorted(const T& item) const
  {
    int left = 0, right = Size();
    while (left != right)
    {
      int mid = (left + right) / 2;
      const T& midValue = (*this)[mid];
      if (item == midValue)
        return mid;
      if (item < midValue)
        right = mid;
      else
        left = mid + 1;
    }
    return -1;
  }
  int AddToSorted(const T& item)
  {
    int left = 0, right = Size();
    while (left != right)
    {
      int mid = (left + right) / 2;
      const T& midValue = (*this)[mid];
      if (item == midValue)
      {
        right = mid + 1;
        break;
      }
      if (item < midValue)
        right = mid;
      else
        left = mid + 1;
    }
    Insert(right, item);
    return right;
  }

  void Sort(int (*compare)(void *const *, void *const *, void *), void *param)
    { CPointerVector::Sort(compare, param); }

  static int CompareObjectItems(void *const *a1, void *const *a2, void * /* param */)
    { return MyCompare(*(*((const T **)a1)), *(*((const T **)a2))); }
  void Sort() { CPointerVector::Sort(CompareObjectItems, 0); }
};

#endif
