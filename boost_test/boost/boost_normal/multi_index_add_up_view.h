﻿
///TODO 待整理
// boost multi_index 插入、更新、遍历
#include "boost_common.h"

using boost::multi_index_container;
using namespace boost::multi_index;

template <class KeyExtractor1, class KeyExtractor2> struct key_from_key {
public:
  typedef typename KeyExtractor1::result_type result_type;

  key_from_key(const KeyExtractor1 &key1_ = KeyExtractor1(),
               const KeyExtractor2 &key2_ = KeyExtractor2())
      : key1(key1_), key2(key2_) {}

  template <typename Arg> result_type operator()(Arg &arg) const {
    return key1(key2(arg));
  }

private:
  KeyExtractor1 key1;
  KeyExtractor2 key2;
};

/* an employee record holds its ID, name and age */

typedef struct sub_ee {
public:
  sub_ee(int i) { grade = i; }
  int grade;
} str_grade;

struct employee_add_up {
  int id;
  std::string name;
  int age;
  int index;
  str_grade grade;

  // employee(int id_,std::string name_,int age_):id(id_),name(name_),age(age_),
  // grade(0){}
  employee_add_up(int in_id, std::string in_name, int in_age, int in_index,
           str_grade in_grade)
      : id(in_id), name(in_name), age(in_age), index(in_index),
        grade(in_grade) {}
};

/* tags for accessing the corresponding indices of employee_set */
struct tag_id {};
struct tag_name {};
struct tag_age {};
struct tag_grade {};
struct tag_index {};

/* see Compiler specifics: Use of member_offset for info on
 * BOOST_MULTI_INDEX_MEMBER
 */

/* Define a multi_index_container of employees with following indices:
 *   - a unique index sorted by employee::int,
 *   - a non-unique index sorted by employee::name,
 *   - a non-unique index sorted by employee::age.
 */

struct id_key
    : composite_key<employee_add_up, BOOST_MULTI_INDEX_MEMBER(employee_add_up, int, id),
                    BOOST_MULTI_INDEX_MEMBER(employee_add_up, std::string, name),
                    BOOST_MULTI_INDEX_MEMBER(employee_add_up, int, age),
                    BOOST_MULTI_INDEX_MEMBER(employee_add_up, int, index)> {};

struct index_key
    : composite_key<employee_add_up, BOOST_MULTI_INDEX_MEMBER(employee_add_up, int, age),
                    BOOST_MULTI_INDEX_MEMBER(employee_add_up, int, index)> {};

typedef multi_index_container<
    // employee,
    boost::shared_ptr<employee_add_up>,
    indexed_by<
        ordered_unique<tag<tag_id>, id_key,
                       composite_key_result_less<id_key::result_type>>,
        hashed_non_unique<tag<tag_name>, BOOST_MULTI_INDEX_MEMBER(
                                            employee_add_up, std::string, name)>,
        ordered_non_unique<tag<tag_age>,
                           BOOST_MULTI_INDEX_MEMBER(employee_add_up, int, age)>,
        hashed_non_unique<tag<tag_index>, index_key,
                          composite_key_result_hash<index_key::result_type>>,
        hashed_non_unique<
            tag<tag_grade>,
            key_from_key<BOOST_MULTI_INDEX_MEMBER(sub_ee, int, grade),
                         BOOST_MULTI_INDEX_MEMBER(employee_add_up, sub_ee, grade)>>>>
    employee_add_up_set;

template <typename type> void print(employee_add_up_set &es) {
  typedef boost::multi_index::index<employee_add_up_set, type>::type age_map1;
  age_map1 &age_ = get<type>(es);
  BOOST_AUTO(age_map_begin, age_.begin());
  for (; age_map_begin != age_.end(); age_map_begin++)
    std::cout << "id:" << (*age_map_begin)->id
              << ", name:" << (*age_map_begin)->name
              << ", age:" << (*age_map_begin)->age
              << ", index:" << (*age_map_begin)->index << ", grade"
              << (*age_map_begin)->grade.grade << std::endl;
}

bool multi_index_add_up_view() {
  employee_add_up_set es;

  es.insert(
      boost::make_shared<employee_add_up>(employee_add_up(0, "1", 55, 0, str_grade(2))));
  es.insert(
      boost::make_shared<employee_add_up>(employee_add_up(1, "1", 20, 1, str_grade(5))));
  es.insert(
      boost::make_shared<employee_add_up>(employee_add_up(2, "2", 40, 2, str_grade(3))));
  es.insert(
      boost::make_shared<employee_add_up>(employee_add_up(2, "1", 10, 4, str_grade(6))));
  es.insert(
      boost::make_shared<employee_add_up>(employee_add_up(2, "2", 35, 5, str_grade(4))));
  es.insert(
      boost::make_shared<employee_add_up>(employee_add_up(6, "1", 80, 6, str_grade(1))));

  print<tag_id>(es);

  //按照 age索引，对容易进行遍历
  typedef boost::multi_index::index<employee_add_up_set, tag_id>::type age_map1;
  age_map1 &age_ = get<tag_id>(es);
  BOOST_AUTO(age_map_per, age_.find(boost::make_tuple(2, "2", 40, 2)));
  boost::shared_ptr<employee_add_up> ptr_tmp = boost::make_shared<employee_add_up>(
      employee_add_up((*age_map_per)->id, (*age_map_per)->name, (*age_map_per)->age,
               (*age_map_per)->index, (*age_map_per)->grade));
  ptr_tmp->age = 30;
  age_.replace(age_map_per, ptr_tmp);
  //(*age_map_per)->age = 30;

  std::cout << std::endl;
  print<tag_id>(es);

  return true;
}