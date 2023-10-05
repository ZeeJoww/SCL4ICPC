vec3 cross(vec3 a, vec3 b) {
    return vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

// rotate vec `v` around vec `k` by an angle `a` 
vec3 rotate3(vec3 v, vec3 k, double a) {
    k = unit(k);
    vec3 kv = cross(k, v);
    return v + std::sin(a) * kv + (1.0 - std::cos(a)) * cross(k, kv);
}

