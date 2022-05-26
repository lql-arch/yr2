package one_way;
//
//public class class_it {
//    protected Object doResolveDependency(DependencyDescriptor descriptor, Class<?> type, String beanName,
//                                         Set<String> autowiredBeanNames, TypeConverter typeConverter) throws BeansException {
//
//        Object value = getAutowireCandidateResolver().getSuggestedValue(descriptor);
//        if (value != null) {
//            if (value instanceof String) {
//                String strVal = resolveEmbeddedValue((String) value);
//                BeanDefinition bd = (beanName != null && containsBean(beanName) ? getMergedBeanDefinition(beanName) : null);
//                value = evaluateBeanDefinitionString(strVal, bd);
//            }
//            TypeConverter converter = (typeConverter != null ? typeConverter : getTypeConverter());
//            return (descriptor.getField() != null ?
//                    converter.convertIfNecessary(value, type, descriptor.getField()) :
//                    converter.convertIfNecessary(value, type, descriptor.getMethodParameter()));
//        }
//
//        if (type.isArray()) {
//            Class<?> componentType = type.getComponentType();
//            Map<String, Object> matchingBeans = findAutowireCandidates(beanName, componentType, descriptor);
//            if (matchingBeans.isEmpty()) {
//                if (descriptor.isRequired()) {
//                    raiseNoSuchBeanDefinitionException(componentType, "array of " + componentType.getName(), descriptor);
//                }
//                return null;
//            }
//            if (autowiredBeanNames != null) {
//                autowiredBeanNames.addAll(matchingBeans.keySet());
//            }
//            TypeConverter converter = (typeConverter != null ? typeConverter : getTypeConverter());
//            return converter.convertIfNecessary(matchingBeans.values(), type);
//        }
//        else if (Collection.class.isAssignableFrom(type) && type.isInterface()) {
//            Class<?> elementType = descriptor.getCollectionType();
//            if (elementType == null) {
//                if (descriptor.isRequired()) {
//                    throw new FatalBeanException("No element type declared for collection [" + type.getName() + "]");
//                }
//                return null;
//            }
//            Map<String, Object> matchingBeans = findAutowireCandidates(beanName, elementType, descriptor);
//            if (matchingBeans.isEmpty()) {
//                if (descriptor.isRequired()) {
//                    raiseNoSuchBeanDefinitionException(elementType, "collection of " + elementType.getName(), descriptor);
//                }
//                return null;
//            }
//            if (autowiredBeanNames != null) {
//                autowiredBeanNames.addAll(matchingBeans.keySet());
//            }
//            TypeConverter converter = (typeConverter != null ? typeConverter : getTypeConverter());
//            return converter.convertIfNecessary(matchingBeans.values(), type);
//        }
//        else if (Map.class.isAssignableFrom(type) && type.isInterface()) {
//            Class<?> keyType = descriptor.getMapKeyType();
//            if (keyType == null || !String.class.isAssignableFrom(keyType)) {
//                if (descriptor.isRequired()) {
//                    throw new FatalBeanException("Key type [" + keyType + "] of map [" + type.getName() +
//                            "] must be assignable to [java.lang.String]");
//                }
//                return null;
//            }
//            Class<?> valueType = descriptor.getMapValueType();
//            if (valueType == null) {
//                if (descriptor.isRequired()) {
//                    throw new FatalBeanException("No value type declared for map [" + type.getName() + "]");
//                }
//                return null;
//            }
//            Map<String, Object> matchingBeans = findAutowireCandidates(beanName, valueType, descriptor);
//            if (matchingBeans.isEmpty()) {
//                if (descriptor.isRequired()) {
//                    raiseNoSuchBeanDefinitionException(valueType, "map with value type " + valueType.getName(), descriptor);
//                }
//                return null;
//            }
//            if (autowiredBeanNames != null) {
//                autowiredBeanNames.addAll(matchingBeans.keySet());
//            }
//            return matchingBeans;
//        }
//        else {
//            Map<String, Object> matchingBeans = findAutowireCandidates(beanName, type, descriptor);
//            if (matchingBeans.isEmpty()) {
//                if (descriptor.isRequired()) {
//                    raiseNoSuchBeanDefinitionException(type, "", descriptor);
//                }
//                return null;
//            }
//            if (matchingBeans.size() > 1) {
//                String primaryBeanName = determinePrimaryCandidate(matchingBeans, descriptor);
//                if (primaryBeanName == null) {
//                    throw new NoUniqueBeanDefinitionException(type, matchingBeans.keySet());
//                }
//                if (autowiredBeanNames != null) {
//                    autowiredBeanNames.add(primaryBeanName);
//                }
//                return matchingBeans.get(primaryBeanName);
//            }
//            // We have exactly one match.
//            Map.Entry<String, Object> entry = matchingBeans.entrySet().iterator().next();
//            if (autowiredBeanNames != null) {
//                autowiredBeanNames.add(entry.getKey());
//            }
//            return entry.getValue();
//        }
//    }
//}
