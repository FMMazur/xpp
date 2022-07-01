#ifndef XPP_SYMBOL_TABLE_HXX
#define XPP_SYMBOL_TABLE_HXX

#include <unordered_map>
#include <string_view>
#include "token.hxx"

namespace xpp {

  struct STEntry {
    Token *token;
    bool reserved{};

    STEntry() = delete;

    explicit STEntry(Token *token) : token{token} {}

    STEntry(Token *token, bool reserved) : token{token}, reserved{reserved} {}
  };

  class SymbolTable {
  public:
    SymbolTable();

    explicit SymbolTable(SymbolTable *parent);

    virtual ~SymbolTable();

    bool add(STEntry *entry);

    bool add(Token *token, bool reserved = false);

    bool remove(std::string_view entry);

    void clear();

    bool empty();

    STEntry *get(std::string_view entry);

    inline SymbolTable *parent() { return _parent; }

  private:
    SymbolTable *_parent;
    std::unordered_map<std::string_view, STEntry *> _symbols;
  };

} // xpp

#endif //XPP_SYMBOL_TABLE_HXX
