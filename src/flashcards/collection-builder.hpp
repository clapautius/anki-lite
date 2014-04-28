#ifndef ANKI_LITE_COLLECTION_BUILDER_HPP_
#define ANKI_LITE_COLLECTION_BUILDER_HPP_

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include "collection.hpp"

namespace anki_lite
{


class CollectionBuilder
{
public:

    CollectionBuilder();

    virtual ~CollectionBuilder() {};

    boost::shared_ptr<Collection> getCollection();

    virtual bool set_conf() = 0;

    virtual bool add_decks() = 0;

    virtual bool add_cards() = 0;

protected:

    boost::shared_ptr<Collection> m_collection;

    bool m_complete;
};


/**
 * Helper class used for tests. (temporary).
 */
class CollectionBuilderHardcoded : public CollectionBuilder
{

public:

    CollectionBuilderHardcoded();

    virtual bool set_conf();

    virtual bool add_decks();

    virtual bool add_cards();
};


class CollectionInitializer
{
public:

    void construct(CollectionBuilder&);

};

}

#endif
