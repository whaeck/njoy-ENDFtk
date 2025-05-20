/**
 *  @brief Return the descriptive data
 */
auto description() const {

  std::string description;
  description.reserve( this->description_.size() * 67 );
  for ( auto&& record : this->description_ ) {

    description += record.text();
    description += '\n';
  }
  return description;
}
