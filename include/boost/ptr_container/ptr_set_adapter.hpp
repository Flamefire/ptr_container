
#ifndef BOOST_PTR_CONTAINER_PTR_SET_ADAPTER_HPP
#define BOOST_PTR_CONTAINER_PTR_SET_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/ptr_container/detail/associative_ptr_container.hpp>
#include <boost/ptr_container/detail/void_ptr_iterator.hpp>
#include <boost/range/reverse_iterator.hpp>
#include <boost/range/const_reverse_iterator.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost
{
    template
    < 
        class Key,
        class VoidPtrSet
    >
    struct set_config
    {
       typedef VoidPtrSet 
                    void_container_type;

       typedef BOOST_DEDUCED_TYPENAME VoidPtrSet::allocator_type 
                    allocator_type;

       typedef Key  value_type;

       typedef value_type 
                    key_type;

       typedef BOOST_DEDUCED_TYPENAME VoidPtrSet::value_compare
                    value_compare;

       typedef value_compare 
                    key_compare;

       typedef ptr_container_detail::void_ptr_iterator<
                       BOOST_DEDUCED_TYPENAME VoidPtrSet::iterator, Key > 
                    ptr_iterator;
       
       typedef boost::indirect_iterator<ptr_iterator> 
                    iterator;

       typedef ptr_container_detail::void_ptr_iterator<
                        BOOST_DEDUCED_TYPENAME VoidPtrSet::const_iterator, const Key >
                    ptr_const_iterator;

       typedef boost::indirect_iterator<ptr_const_iterator>
                    const_iterator;

       typedef ptr_container_detail::void_ptr_iterator<
                       BOOST_DEDUCED_TYPENAME VoidPtrSet::reverse_iterator, Key >
                   ptr_reverse_iterator;
        
       typedef boost::indirect_iterator<ptr_reverse_iterator>
                   reverse_iterator;

       typedef ptr_container_detail::void_ptr_iterator<
                       BOOST_DEDUCED_TYPENAME VoidPtrSet::const_reverse_iterator, const Key >
                   ptr_const_reverse_iterator;

       typedef boost::indirect_iterator<ptr_const_reverse_iterator>
                   const_reverse_iterator;
       
       typedef Key object_type;

       template< class Iter >
       static BOOST_DEDUCED_TYPENAME Iter::wrapped_type get_base( Iter i )
       {
           return i.base();
       }

       BOOST_STATIC_CONSTANT(bool, allow_null = false );
    };

 
    
    template
    < 
        class Key,
        class VoidPtrSet, 
        class CloneAllocator = heap_clone_allocator
    >
    class ptr_set_adapter_base 
        : public ptr_container_detail::associative_ptr_container< set_config<Key,VoidPtrSet>,
                                                      CloneAllocator >
    {
        typedef ptr_container_detail::associative_ptr_container< set_config<Key,VoidPtrSet>,
                                                     CloneAllocator >
              base_type;
    public:  
        typedef BOOST_DEDUCED_TYPENAME base_type::iterator 
                      iterator;
        typedef BOOST_DEDUCED_TYPENAME base_type::const_iterator 
                      const_iterator;
        typedef BOOST_DEDUCED_TYPENAME base_type::ptr_iterator 
                      ptr_iterator;
        typedef BOOST_DEDUCED_TYPENAME base_type::ptr_const_iterator 
                      ptr_const_iterator;
        typedef BOOST_DEDUCED_TYPENAME base_type::object_type 
                      key_type;

        typedef BOOST_DEDUCED_TYPENAME base_type::size_type
                      size_type;
        
    public:
       template< class Compare, class Allocator >
       ptr_set_adapter_base( const Compare& comp,
                             const Allocator& a ) 
         : base_type( comp, a ) 
       { }

       template< class InputIterator, class Compare, class Allocator >
       ptr_set_adapter_base( InputIterator first, InputIterator last,
                             const Compare& comp,
                             const Allocator& a ) 
         : base_type( first, last, comp, a ) 
       { }

        template< class PtrContainer >
        ptr_set_adapter_base( std::auto_ptr<PtrContainer> clone )
         : base_type( clone )
        { }
        
        template< typename PtrContainer >
        void operator=( std::auto_ptr<PtrContainer> clone )    
        {
            base_type::operator=( clone );
        }
                                                                                                             
        iterator find( const key_type& x )                                                
        {                                                                            
            return iterator( this->c_private().
                             find( const_cast<key_type*>(&x) ) );                                
        }                                                                            

        const_iterator find( const key_type& x ) const                                    
        {                                                                            
            return const_iterator( this->c_private().
                                   find( const_cast<key_type*>(&x) ) );                          
        }                                                                            

        size_type count( const key_type& x ) const                                        
        {                                                                            
            return this->c_private().count( const_cast<key_type*>(&x) );                                           
        }                                                                            
                                                                                     
        iterator lower_bound( const key_type& x )                                         
        {                                                                            
            return iterator( this->c_private().
                             lower_bound( const_cast<key_type*>(&x) ) );                         
        }                                                                            
                                                                                     
        const_iterator lower_bound( const key_type& x ) const                             
        {                                                                            
            return const_iterator( this->c_private().
                                   lower_bound( const_cast<key_type*>(&x) ) );                   
        }                                                                            
                                                                                     
        iterator upper_bound( const key_type& x )                                         
        {                                                                            
            return iterator( this->c_private().
                             upper_bound( const_cast<key_type*>(&x) ) );                         
        }                                                                            
                                                                                     
        const_iterator upper_bound( const key_type& x ) const                             
        {                                                                            
            return const_iterator( this->c_private().
                                   upper_bound( const_cast<key_type*>(&x) ) );                   
        }                                                                            
                                                                                     
        iterator_range<iterator> equal_range( const key_type& x )                    
        {                                                                            
            std::pair<ptr_iterator,ptr_iterator> p = this->c_private().
                equal_range( const_cast<key_type*>(&x) );   
            return make_iterator_range( iterator( p.first ), 
                                        iterator( p.second ) );      
        }                                                                            
                                                                                     
        iterator_range<const_iterator> equal_range( const key_type& x ) const  
        {                                                                            
            std::pair<ptr_const_iterator,ptr_const_iterator> p = this->c_private().
                equal_range( const_cast<key_type*>(&x) ); 
            return make_iterator_range( const_iterator( p.first ), 
                                        const_iterator( p.second ) );    
        }                                                                            
                                                                                     
        key_type& at( const key_type& key )                                              
        {                                                                            
           iterator i = this->find( key );                                           
           if( i != this->end() )                                                    
               return *i;                                                            
           else                                                                      
               throw bad_ptr_container_operation( "'at()' could not find key" ); 
        }                                                                            
                                                                                     
        const key_type& at( const key_type& key ) const                                  
        {                                                                            
           const_iterator i = this->find( key );                                           
           if( i != this->end() )                                                    
               return *i;                                                            
           else                                                                      
               throw bad_ptr_container_operation( "'at()' could not find key" ); 
        }
    };
    
    /////////////////////////////////////////////////////////////////////////
    // ptr_set_adapter
    /////////////////////////////////////////////////////////////////////////
  
    template
    <
        class Key,
        class VoidPtrSet, 
        class CloneAllocator = heap_clone_allocator
    >
    class ptr_set_adapter : 
        public ptr_set_adapter_base<Key,VoidPtrSet,CloneAllocator>
    {
        typedef ptr_set_adapter_base<Key,VoidPtrSet,CloneAllocator> 
            base_type;
    
    public: // typedefs
       
        typedef BOOST_DEDUCED_TYPENAME base_type::iterator
                     iterator;                 
        typedef BOOST_DEDUCED_TYPENAME base_type::const_iterator
                     const_iterator;                 
        typedef BOOST_DEDUCED_TYPENAME base_type::ptr_iterator
                     ptr_iterator;   
        typedef BOOST_DEDUCED_TYPENAME base_type::size_type
                     size_type;    
        typedef BOOST_DEDUCED_TYPENAME base_type::object_type
                     key_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::auto_type
                     auto_type;
        typedef BOOST_DEDUCED_TYPENAME VoidPtrSet::key_compare
                      key_compare;
        typedef BOOST_DEDUCED_TYPENAME VoidPtrSet::allocator_type
                      allocator_type;        
    private:
        
        template< typename II >                                               
        void set_basic_clone_and_insert( II first, II last ) // basic                 
        {                                                                     
            while( first != last )                                            
            {           
                if( this->find( *first ) == this->end() )
                    insert( CloneAllocator::allocate_clone( *first ) ); // strong, commit
                ++first;                                                      
            }                                                                 
        }                         

    public:
        
        explicit ptr_set_adapter( const key_compare& comp = key_compare(),
                                  const allocator_type& a = allocator_type() ) 
          : base_type( comp, a ) 
        {
            BOOST_ASSERT( this->empty() ); 
        }
        
        template< class InputIterator, class Compare, class Allocator >
        ptr_set_adapter( InputIterator first, InputIterator last, 
                         const Compare& comp = Compare(),
                         const Allocator a = Allocator() )
          : base_type( comp, a )
        {
            BOOST_ASSERT( this->empty() );
            set_basic_clone_and_insert( first, last );
        }

        template< class T >
        ptr_set_adapter( std::auto_ptr<T> r ) : base_type( r )
        { }

        template< class T >
        void operator=( std::auto_ptr<T> r ) 
        {
            base_type::operator=( r );
        }

        std::pair<iterator,bool> insert( key_type* x ) // strong                      
        {       
            this->enforce_null_policy( x, "Null pointer in 'ptr_set::insert()'" );
            
            auto_type ptr( x );                                
            std::pair<ptr_iterator,bool> res = this->c_private().insert( x );       
            if( res.second )                                                 
                ptr.release();                                                  
            return std::make_pair( iterator( res.first ), res.second );     
        }

        
        iterator insert( iterator where, key_type* x ) // strong
        {
            this->enforce_null_policy( x, "Null pointer in 'ptr_set::insert()'" );

            auto_type ptr( x );                                
            ptr_iterator res = this->c_private().insert( where.base().base(), x );
            if( *res == x )                                                 
                ptr.release();                                                  
            return iterator( res);
        }
        
        template< typename InputIterator >
        void insert( InputIterator first, InputIterator last ) // basic
        {
            set_basic_clone_and_insert( first, last );
        }

        template< class Range >
        BOOST_DEDUCED_TYPENAME
        boost::disable_if< ptr_container_detail::is_pointer_or_integral<Range> >::type
        insert( const Range& r )
        {
            insert( this->adl_begin(r), this->adl_end(r) );
        }
        
        bool transfer( iterator object, 
                       ptr_set_adapter& from ) // strong
        {
            return this->single_transfer( object, from );
        }

        size_type transfer( iterator first, 
                            iterator last, 
                            ptr_set_adapter& from ) // basic
        {
            return this->single_transfer( first, last, from );
        }

        template< class Range >
        BOOST_DEDUCED_TYPENAME boost::disable_if< boost::is_same< Range,
                                                                  iterator >,
                                                            size_type >::type
        transfer( const Range& r, ptr_set_adapter& from ) // basic
        {
            return transfer( this->adl_begin(r), this->adl_end(r), from );
        }


        size_type transfer( ptr_set_adapter& from ) // basic
        {
            return transfer( from.begin(), from.end(), from );
        }

    };
    
    /////////////////////////////////////////////////////////////////////////
    // ptr_multiset_adapter
    /////////////////////////////////////////////////////////////////////////

    template
    < 
        class Key,
        class VoidPtrMultiSet, 
        class CloneAllocator = heap_clone_allocator 
    >
    class ptr_multiset_adapter : 
        public ptr_set_adapter_base<Key,VoidPtrMultiSet,CloneAllocator>
    {
         typedef ptr_set_adapter_base<Key,VoidPtrMultiSet,CloneAllocator> base_type;
    
    public: // typedefs
    
        typedef BOOST_DEDUCED_TYPENAME base_type::iterator   
                       iterator;          
        typedef BOOST_DEDUCED_TYPENAME base_type::ptr_iterator
                       ptr_iterator;
        typedef BOOST_DEDUCED_TYPENAME base_type::size_type
                       size_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::object_type
                      key_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::auto_type
                      auto_type;
        typedef BOOST_DEDUCED_TYPENAME VoidPtrMultiSet::key_compare
                      key_compare;
        typedef BOOST_DEDUCED_TYPENAME VoidPtrMultiSet::allocator_type
                      allocator_type;        
    private:
        template< typename II >                                               
        void set_basic_clone_and_insert( II first, II last ) // basic                 
        {                                                                     
            while( first != last )                                            
            {           
                insert( CloneAllocator::allocate_clone( *first ) ); // strong, commit                              
                ++first;                                                      
            }                                                                 
        }                         
    
    public:

        explicit ptr_multiset_adapter( const key_compare& comp = key_compare(),
                                       const allocator_type& a = allocator_type() )
        : base_type( comp, a ) 
        { }
    
        template< class InputIterator >
        ptr_multiset_adapter( InputIterator first, InputIterator last,
                              const key_compare& comp = key_compare(),
                              const allocator_type& a = allocator_type() )
        : base_type( comp, a ) 
        {
            set_basic_clone_and_insert( first, last );
        }

        template< class T >
        ptr_multiset_adapter( std::auto_ptr<T> r ) : base_type( r )
        { }

        template< class T >
        void operator=( std::auto_ptr<T> r ) 
        {
            base_type::operator=( r ); 
        }

        iterator insert( iterator before, key_type* x ) // strong  
        {
            return base_type::insert( before, x ); 
        } 
    
        iterator insert( key_type* x ) // strong                                      
        {   
            this->enforce_null_policy( x, "Null pointer in 'ptr_multiset::insert()'" );
    
            auto_type ptr( x );                                
            ptr_iterator res = this->c_private().insert( x );                         
            ptr.release();                                                      
            return iterator( res );                                             
        }
    
        template< typename InputIterator >
        void insert( InputIterator first, InputIterator last ) // basic
        {
            set_basic_clone_and_insert( first, last );
        }

        template< class Range >
        BOOST_DEDUCED_TYPENAME
        boost::disable_if< ptr_container_detail::is_pointer_or_integral<Range> >::type
        insert( const Range& r )
        {
            insert( this->adl_begin(r), this->adl_end(r) );
        }

        void transfer( iterator object, 
                       ptr_multiset_adapter& from ) // strong
        {
            this->multi_transfer( object, from );
        }

        size_type transfer( iterator first, 
                            iterator last, 
                            ptr_multiset_adapter& from ) // basic
        {
            return this->multi_transfer( first, last, from );
        }

        template< class Range >
        BOOST_DEDUCED_TYPENAME boost::disable_if< boost::is_same< Range,
                                           iterator >, size_type >::type
        transfer(  const Range& r, ptr_multiset_adapter& from ) // basic
        {
            return transfer( this->adl_begin(r), this->adl_end(r), from );
        }

        void transfer( ptr_multiset_adapter& from ) // basic
        {
            transfer( from.begin(), from.end(), from );
            BOOST_ASSERT( from.empty() );
        }
    };

} // namespace 'boost'  

#endif