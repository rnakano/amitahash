#include <gtest/gtest.h>

extern "C" {
#include "table.h"
#include "bucket.h"
}

TEST(BucketTest, search) 
{
  ah_bucket* bucket = ah_bucket_create_empty();
  ah_bucket_insert(&bucket, "key1", "value1");
  ah_bucket_insert(&bucket, "key2", "value2");

  ASSERT_STREQ("value1", 
               ah_bucket_search(bucket, "key1")->value);
  ASSERT_STREQ("value2",
               ah_bucket_search(bucket, "key2")->value);
  EXPECT_EQ(NULL, ah_bucket_search(bucket, "key_none"));
}

TEST(BucketTest, length)
{
  ah_bucket* bucket = ah_bucket_create_empty();
  ah_bucket_insert(&bucket, "key1", "value1");
  ASSERT_EQ(1, ah_bucket_length(bucket));
  ah_bucket_insert(&bucket, "key2", "value2");
  ASSERT_EQ(2, ah_bucket_length(bucket));
}

TEST(BucketTest, remove)
{
  ah_bucket* bucket = ah_bucket_create_empty();
  ah_bucket_insert(&bucket, "key1", "value1");
  ah_bucket_insert(&bucket, "key2", "value2");
  ah_bucket_remove(&bucket, "key_none");
  ASSERT_EQ(2, ah_bucket_length(bucket));
  ah_bucket_remove(&bucket, "key2");
  ASSERT_EQ(1, ah_bucket_length(bucket));
  ah_bucket_remove(&bucket, "key1");
  ASSERT_EQ(0, ah_bucket_length(bucket));
  ah_bucket_remove(&bucket, "key_none");
  ASSERT_EQ(0, ah_bucket_length(bucket));
  EXPECT_EQ(NULL, bucket);
}

TEST(BucketTest, removeReverse)
{
  ah_bucket* bucket = ah_bucket_create_empty();
  ah_bucket_insert(&bucket, "key1", "value1");
  ah_bucket_insert(&bucket, "key2", "value2");
  ah_bucket_remove(&bucket, "key1");
  ASSERT_EQ(1, ah_bucket_length(bucket));
  ah_bucket_remove(&bucket, "key2");
  ASSERT_EQ(0, ah_bucket_length(bucket));
  EXPECT_EQ(NULL, bucket);
}

TEST(BucketTest, delete)
{
  ah_bucket* bucket = ah_bucket_create_empty();
  ah_bucket_delete(bucket);
  bucket = ah_bucket_create_empty();
  ah_bucket_insert(&bucket, "key1", "value1");
  ah_bucket_insert(&bucket, "key1", "value1");
  ah_bucket_delete(bucket);
}

TEST(TableTest, setget)
{
  ah_table* table = ah_table_create(100);
  ah_table_set(table, "key1", "value1");
  ah_table_set(table, "key2", "value2");
  ASSERT_STREQ("value1", ah_table_get(table, "key1"));
  ASSERT_STREQ("value2", ah_table_get(table, "key2"));

  ah_table_set(table, "akey", "avalue");
  ASSERT_STREQ("avalue", ah_table_get(table, "akey"));
}

TEST(TableTest, getForNone)
{
  ah_table* table = ah_table_create(100);
  EXPECT_EQ(NULL, ah_table_get(table, "key1"));
}

TEST(TableTest, remove)
{
  ah_table* table = ah_table_create(100);
  ah_table_set(table, "key1", "value1");
  ah_table_set(table, "key2", "value2");
  
  ah_table_remove(table, "key1");
  EXPECT_EQ(NULL, ah_table_get(table, "key1"));
  ah_table_remove(table, "key2");
  EXPECT_EQ(NULL, ah_table_get(table, "key2"));
}

TEST(TableTest, deleteTable)
{
  ah_table* table = ah_table_create(100);
  ah_table_set(table, "key1", "value1");
  ah_table_set(table, "key2", "value2");
  ah_table_delete(table);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
