#include <vector>
#include "collection-builder.hpp"

using std::vector;

/* CollectionBuilder class */

namespace anki_lite
{

CollectionBuilder::CollectionBuilder()
  : m_complete(false)
{
    m_collection.reset(new Collection);
}


boost::shared_ptr<Collection> CollectionBuilder::getCollection()
{
    if (!m_complete) {
        m_collection.reset();
    }
    return m_collection;
}


/* CollectionBuilderHardcoded class */

bool CollectionBuilderHardcoded::set_conf()
{
    bool rc = true;
    TextMapT conf;
    conf["name"] = "collection";
    m_collection->set_conf(conf);
    return rc;
}


bool CollectionBuilderHardcoded::add_decks()
{
    bool rc = true;
    vector<TextMapT> decks;
    TextMapT deck;
    deck["id"] = 5;
    deck["name"] = "default";
    decks.push_back(deck);
    m_collection->set_decks(decks);
    return rc;
}


bool CollectionBuilderHardcoded::add_cards()
{
    bool rc = true;
    boost::shared_ptr<Card> card(new Card(5, "front", "back"));
    m_collection->get_deck_by_idx(0).add_card(card);
    return rc;
}


/* CollectionInitializer class */

void CollectionInitializer::construct(CollectionBuilder &builder)
{
    builder.set_conf();
    builder.add_decks();
    builder.add_cards();
}

} // namespace anki_lite
