
HashTable::HashTable(size_t size) : _capacity(size), _filled(0), table(size) {
}

HashTable::~HashTable() = default{
}

void HashTable::insert(const KeyType &key, const ValueType &value){
  if (_filled >= _capacity){
    return;
  }
  if (getLoadFactor() > 0.75){
    _capacity *= 2;
    HashTable newTable(_capacity);
    for (auto&  lis: table) {
      for (const auto& pair : lis) {
         newTable[hash_function(pair.first)].push_back(pair);
      }
    }
    //std::swap(table, newTable.table);
    table = newTable;
  }
  
  for (auto &pair : table[hash_function(key)]) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    table[hash_function(key)].emplace_back(key, value);
    _filled++;
}

void HashTable::find(const KeyType& key, ValueType &value){
  for (auto &lis : table){
    for (auto &pair : lis){
      if (pair.first == key){
        value = pair.second;
        return true;
      }
    }
  }
  return false;
}

void HashTable::remove(const Key &key){
  for (auto& lis : table){
    for (auto it = lis.begin(); it != lis.end(); ++it){
      if (it->first == key){
        lis.erase(it);
        _filled--;
        return;
      }
    }
  }
}

ValueType &HashTable::operator[](const KeyType &key) {
  for (auto &lis : table){
    for (auto &pair : lis){
      if (pair.first == key){
        return pair.second;
      }
    }
  }
}

size_t HashTable::getLoadFactor() const{
  return static_cast<double>(_filled) / _capacity;
}

size_t HashTable::hash_function(const KeyType &key) const {
    size_t hash = 0;
    for (auto &c : key) {
        hash = (hash * 127 + c) % _capacity;
    }
    return hash;
}

int main(){
  return 0;
}
