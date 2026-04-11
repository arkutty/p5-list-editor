#include "TextBuffer.hpp"

//EFFECTS: Creates an empty text buffer. Its cursor is at the past-the-end
//         position, with row 1, column 0, and index 0.
TextBuffer::TextBuffer():row(1), column(0), index(0){
    CharList n_data;
    this->data = n_data;
    this->cursor = data.begin();
}

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor one position forward and returns true,
  //          unless the cursor is already at the past-the-end position,
  //          in which case this does nothing and returns false.
  //NOTE:     Your implementation must update the row, column, and index
//          if appropriate to maintain all invariants.
bool TextBuffer::forward(){
    if (cursor == data.end()){
      return false;
    }
    if (*cursor == '\n'){
        column = 0;
        ++row;
    } else {
        ++column;
    }
    ++cursor;
    ++index;
    return true;
}

bool TextBuffer::backward(){
    if (cursor == data.begin()){
      return false;
    }
    --cursor;
    --index;
    if (*cursor == '\n'){
        --row;
        column = compute_column();
    } else {
        --column;
    }
    return true;
}

void TextBuffer::insert(char c){
    data.insert(cursor, c);
    if (c == '\n'){
        row++;
        column = 0;
    } else {
        ++column;
      
    }
    ++index;
    
}

  //MODIFIES: *this
  //EFFECTS:  Removes the character from the buffer that is at the cursor and
  //          returns true, unless the cursor is at the past-the-end position,
  //          in which case this does nothing and returns false.
  //          The cursor will now point to the character that was after the
  //          deleted character, or the past-the-end position if the deleted
  //          character was the last one in the buffer.
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
bool TextBuffer::remove(){
    if (cursor == data.end()){
        return false;
    }
    if (*cursor == '\n'){
        --row;
        column = compute_column();
    }  
    cursor = data.erase(cursor);
    return true;
}

void TextBuffer::move_to_row_start(){
    while (cursor != data.begin() && (cursor == data.end() || *cursor != '\n')){
      --cursor;
      --index;
    }
    if (cursor != data.end() && *cursor == '\n'){
        ++cursor;
        ++index;
    }
    column = 0;
}

void TextBuffer::move_to_row_end(){
    while (cursor != data.end() && *cursor != '\n'){
      ++cursor;
      ++column;
      ++index;
    }
}

  //REQUIRES: new_column >= 0
  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the given column in the current row,
  //          if it exists. If the row does not have that many columns,
  //          moves to the end of the row (the newline character that
  //          ends the row, or the past-the-end position if the row is
  //          the last one in the buffer).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
void TextBuffer::move_to_column(int new_column){
    move_to_row_start();
    while (column < new_column && cursor != data.end()){
        ++cursor;
        ++column;
        ++index;
        if (cursor != data.end() && *cursor == '\n'){
            break;
        }
    }
}

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the previous row, retaining the
  //          current column if possible. If the previous row is
  //          shorter than the current column, moves to the end of the
  //          previous row (the newline character that ends the row).
  //          Does nothing if the cursor is already in the first row.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already in the first row).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
bool TextBuffer::up(){
    if (row == 1){
        return false;
    }
    int below_length = column;
    move_to_row_start();
    backward();
    if (column < below_length){
        return true;
    } else {
        move_to_row_start();
        move_to_column(below_length);
        return true;
    }
}

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the next row, retaining the current
  //          column if possible. If the next row is shorter than the
  //          current column, moves to the end of the next row (the
  //          newline character that ends the row, or the past-the-end
  //          position if the row is the last one in the buffer). Does
  //          nothing if the cursor is already in the last row.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already in the last row).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
bool TextBuffer::down(){
    if (cursor == data.end()){
        return false;
    }
    int length_above = column;
    move_to_row_end();
    if (is_at_end()){
        return false;
    }
    ++row;
    move_to_row_start();
    move_to_column(length_above);
    return true;
    
}

bool TextBuffer::is_at_end() const{
    if (data.end() == cursor){
      return true;
    } else {
      return false;
    }
}

char TextBuffer::data_at_cursor() const{
    return *cursor;
}

int TextBuffer::get_row() const{
    return row;
}

int TextBuffer::get_column() const{
    return column;
}

int TextBuffer::get_index() const{
    return index;
}

int TextBuffer::size() const{
    return data.size();
}

std::string TextBuffer::stringify() const{
    return std::string(data.begin(), data.end());
}

int TextBuffer::compute_column() const{
    if (cursor == data.begin()){
        return 0;
    }
    Iterator temp_cursor(cursor);
    int char_count = 0;
    --temp_cursor;
    while (*temp_cursor != '\n'){
        ++char_count;
        if (temp_cursor == data.begin()){
            break;
        }
        --temp_cursor;
    }
    return char_count;
}