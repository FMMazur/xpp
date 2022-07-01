#include "symbol_table.hxx"

namespace xpp {
  SymbolTable::SymbolTable() : _parent{nullptr}, _symbols{} {

  }

  SymbolTable::SymbolTable(SymbolTable *parent) : _parent{parent}, _symbols{} {

  }

  SymbolTable::~SymbolTable() {
    _parent = nullptr;

    for (auto const &[_, entry]: _symbols) {
      delete entry;
    }

    _symbols.clear();
  }

  bool SymbolTable::add(STEntry *entry) {
    if (_symbols.find(entry->token->lexeme()) != _symbols.end())
      return false;

    _symbols.insert({entry->token->lexeme(), entry});

    return true;
  }

  bool SymbolTable::add(Token *token, bool reserved) {
    auto entry = new STEntry(token, reserved);

    return add(entry);
  }

  bool SymbolTable::remove(std::string_view entry) {
    return _symbols.erase(entry) != 0;
  }

  void SymbolTable::clear() {
    _symbols.clear();
  }

  bool SymbolTable::empty() {
    return _symbols.empty();
  }

  STEntry *SymbolTable::get(std::string_view entry) {
    auto table = this;

    auto st = table->_symbols.find(entry);

    while (st == _symbols.end()) {
      table = table->_parent;

      if (table == nullptr)
        return nullptr;

      st = table->_symbols.find(entry);
    }

    return st->second;
  }
} // xpp