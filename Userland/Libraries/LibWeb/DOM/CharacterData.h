/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/String.h>
#include <AK/Utf16View.h>
#include <LibLocale/Forward.h>
#include <LibWeb/DOM/ChildNode.h>
#include <LibWeb/DOM/Node.h>
#include <LibWeb/DOM/NonDocumentTypeChildNode.h>

namespace Web::DOM {

// https://dom.spec.whatwg.org/#characterdata
class CharacterData
    : public Node
    , public ChildNode<CharacterData>
    , public NonDocumentTypeChildNode<CharacterData> {
    WEB_PLATFORM_OBJECT(CharacterData, Node);
    JS_DECLARE_ALLOCATOR(CharacterData);

public:
    virtual ~CharacterData() override;

    String const& data() const { return m_data; }
    void set_data(String const&);

    unsigned length_in_utf16_code_units() const
    {
        return AK::utf16_code_unit_length_from_utf8(m_data);
    }

    WebIDL::ExceptionOr<String> substring_data(size_t offset_in_utf16_code_units, size_t count_in_utf16_code_units) const;
    WebIDL::ExceptionOr<void> append_data(String const&);
    WebIDL::ExceptionOr<void> insert_data(size_t offset_in_utf16_code_units, String const&);
    WebIDL::ExceptionOr<void> delete_data(size_t offset_in_utf16_code_units, size_t count_in_utf16_code_units);
    WebIDL::ExceptionOr<void> replace_data(size_t offset_in_utf16_code_units, size_t count_in_utf16_code_units, String const&);

    Locale::Segmenter& grapheme_segmenter() const;
    Locale::Segmenter& word_segmenter() const;

protected:
    CharacterData(Document&, NodeType, String const&);

    virtual void initialize(JS::Realm&) override;

private:
    String m_data;

    mutable OwnPtr<Locale::Segmenter> m_grapheme_segmenter;
    mutable OwnPtr<Locale::Segmenter> m_word_segmenter;
};

}
